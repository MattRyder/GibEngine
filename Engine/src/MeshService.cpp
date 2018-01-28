#include "MeshService.h"
#include <chrono>

#define BENCHMARK(FUNC) {\
auto clock = std::chrono::high_resolution_clock::now();\
FUNC;\
auto clockEnd = std::chrono::high_resolution_clock::now();\
auto time = std::chrono::duration_cast<std::chrono::milliseconds>(clockEnd - clock).count();\
Logger::Instance->info("BENCHMARK TIME: {}ms", time);\
}

void GibEngine::MeshService::ProcessNode(File* rootMeshFile, Scene::Node* parentNode, const aiScene* scene, Mesh::Flags flags, aiNode* node)
{
	// Load each mesh for this node:
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		unsigned int meshIndex = node->mMeshes[i];
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Material*> materials;

		aiMesh* mesh = scene->mMeshes[meshIndex];
		const char* name = mesh->mName.C_Str();
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiMatrix4x4 t = node->mTransformation;
		glm::mat4 meshTransform = glm::mat4
		(
			t.a1, t.a2, t.a3, t.a4,
			t.b1, t.b2, t.b3, t.b4,
			t.c1, t.c2, t.c3, t.c4,
			t.d1, t.d2, t.d3, t.d4
		);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			if (mesh->HasTangentsAndBitangents())
			{
				const aiVector3D* tangent = &(mesh->mTangents[i]);
				const aiVector3D* bitangent = &(mesh->mBitangents[i]);
				const aiVector3D* normal = &(mesh->mNormals[i]);

				vertex.Tangent = glm::vec3(tangent->x, tangent->y, tangent->z);
				vertex.Bitangent = glm::vec3(bitangent->x, bitangent->y, bitangent->z);
				vertex.Normal = glm::vec3(normal->x, normal->y, normal->z);
				//float det = dot(cross(vertex.Normal, vertex.Tangent), vertex.Bitangent);
				//vertex.Determinant = (det < 0.0f) ? -1.0f : 1.0f;
			}

			vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
				vertex.TexCoord = texCoord;
			}
			else
			{
				vertex.TexCoord = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}
		
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		auto mat = LoadMaterial(scene, rootMeshFile->GetDirectory(), material);

		Mesh* processedMesh = new Mesh(name, rootMeshFile->GetAssetName(), vertices, indices, mat);
		processedMesh->SetFlags(flags);

		Scene::Node* childMeshNode = new Scene::Node(name);
		childMeshNode->SetEntity(processedMesh);
		childMeshNode->SetLocalTransform(meshTransform);

		// Set the database record up:
		childMeshNode->GetDatabaseRecord()->SetState(World::DatabaseRecord::State::CLEAN);

		parentNode->AddChildNode(childMeshNode);
		parentNode->SetFlags(parentNode->GetFlags() ^ Scene::Node::Flags::MESH_ROOT);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(rootMeshFile, parentNode, scene, flags, node->mChildren[i]);
	}
}

GibEngine::Material* GibEngine::MeshService::LoadMaterial(const aiScene* scene, const char* meshDirectory, const aiMaterial* aiMat)
{
	// Load Material for Mesh:
	Material* material = new Material();

	aiColor3D amb, diff, spec;
	float opacity;
	int shine;

	aiMat->Get(AI_MATKEY_COLOR_SPECULAR, spec);
	aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, diff);
	aiMat->Get(AI_MATKEY_COLOR_AMBIENT, amb);
	aiMat->Get(AI_MATKEY_SHININESS, shine);
	aiMat->Get(AI_MATKEY_OPACITY, opacity);

	material->AmbientColor = glm::vec3(amb.r, amb.g, amb.b);
	material->DiffuseColor = glm::vec3(diff.r, diff.g, diff.b);
	material->SpecularColor = glm::vec3(spec.r, spec.g, spec.b);
	material->Opacity = opacity;
	material->Shininess = shine;

	std::map<aiTextureType, TextureType> textureTypes =
	{
		{aiTextureType_DIFFUSE, TextureType::DIFFUSE},
		{aiTextureType_HEIGHT, TextureType::NORMAL},
		{aiTextureType_SPECULAR, TextureType::SPECULAR}
	};


	// TODO: Improve the speed of this, it's ~250ms
	//Yep threading this will massively improve load times.
	for (auto texTypePair : textureTypes)
	{
		auto loadTextureAsync = [](Material* material, const aiScene* scene, const char* meshDirectory, const aiMaterial* aiMat, aiTextureType aiTexType, TextureType engineTexType) {
			std::vector<MaterialTexture*> textureList = LoadMaterialTextures(scene, meshDirectory, aiMat, aiTexType, engineTexType);
			material->Textures.insert(material->Textures.end(), textureList.begin(), textureList.end());
		};

		loadTextureAsync(material, scene, meshDirectory, aiMat, texTypePair.first, texTypePair.second);
	}

	return material;
}

GibEngine::Mesh::Flags GibEngine::MeshService::ParseFlagsJson(const std::vector<json11::Json>& renderFlagsJsonArray)
{
	Mesh::Flags flags = Mesh::Flags::RENDER_ENABLED;

	for (auto renderFlagStr : renderFlagsJsonArray)
	{
		auto flagStrValue = renderFlagStr.string_value();
		if (flagStrValue.compare("RENDER_WIREFRAME") == 0)
		{
			flags ^= Mesh::Flags::RENDER_WIREFRAME;
		}
		else if (flagStrValue.compare("RENDER_DEFERRED") == 0)
		{
			flags ^= Mesh::Flags::RENDER_DEFERRED;
		}
		else if (flagStrValue.compare("RENDER_FORWARD") == 0)
		{
			flags ^= Mesh::Flags::RENDER_FORWARD;
		}
	}

	return flags;
}

std::vector<GibEngine::MaterialTexture*> GibEngine::MeshService::LoadMaterialTextures(const aiScene* scene, const char* meshDirectory, const aiMaterial* material, aiTextureType type, GibEngine::TextureType textureType)
{
	MaterialTexture* matTex = nullptr;
	Texture* texture = nullptr;
	std::vector<MaterialTexture*> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) 
	{
		aiString str;
		material->GetTexture(type, i, &str);

		if (str.C_Str()[0] == '*')
		{
			// Go get the embedded texture for the index in `str`
			int sceneTextureIndex = atoi(&str.C_Str()[1]);

			const aiTexture* sceneTexture = scene->mTextures[sceneTextureIndex];

			// Deal with the hints revealed by aiTexture:
			bool isCompressedTexture = false;
			if (sceneTexture->mHeight == 0)
			{
				// This texture is a compressed texture
				isCompressedTexture = true;
			}

			if (isCompressedTexture)
			{
				unsigned char* compressedTextureData = reinterpret_cast<unsigned char*>(sceneTexture->pcData);
				std::string* textureName = new std::string(str.C_Str());
				texture = Texture::LoadFromMemory(textureType, textureName, compressedTextureData, sceneTexture->mWidth);
				delete compressedTextureData;
			}
		}
		else
		{
			std::string* texturePath = new std::string(meshDirectory);
			texturePath->append("//");
			texturePath->append(str.C_Str());

			texture = Texture::Load(textureType, texturePath);
		}

		matTex = new MaterialTexture();
		matTex->texture = texture;
		
		textures.push_back(matTex);
	}

	return textures;
}

GibEngine::Scene::Node* GibEngine::MeshService::Load(File* file, json11::Json* generationData)
{
	Mesh::Flags genDataMeshFlags = Mesh::Flags::RENDER_ENABLED;

	Assimp::Importer importer;
	const int importerFlags = aiProcess_Triangulate | aiProcess_FlipUVs;
	
	if (generationData != nullptr)
	{
		genDataMeshFlags = ParseFlagsJson(generationData[0]["MeshFlags"].array_items());
	}

	const aiScene* scene = importer.ReadFile(file->GetPath(), importerFlags);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Logger::Instance->error("Failed to load Mesh: {}", importer.GetErrorString());
		return nullptr;
	}

	Scene::Node* rootNode = new Scene::Node("Mesh Root");
	rootNode->SetFlags(rootNode->GetFlags() ^ Scene::Node::Flags::MESH_ROOT);
	ProcessNode(file, rootNode, scene, genDataMeshFlags, scene->mRootNode);
	rootNode->GetDatabaseRecord()->SetState(World::DatabaseRecord::State::CLEAN);
	importer.FreeScene();

	return rootNode;
}

GibEngine::Scene::Node* GibEngine::MeshService::Generate(json11::Json* generationData)
{
	std::string meshType = generationData[0]["MeshType"].string_value();
	if (meshType.compare("Plane") == 0)
	{
		int length = generationData[0]["Length"].int_value();
		int width = generationData[0]["Width"].int_value();
		int intervalSize = generationData[0]["IntervalSize"].int_value();

		Scene::Node* generatedPlaneNode = GeneratePlane(length, width, intervalSize, Mesh::Flags::RENDER_ENABLED);
		Mesh* planeMesh = reinterpret_cast<Mesh*>(generatedPlaneNode->GetEntity());
		planeMesh->SetGenerationData(generationData);

		return generatedPlaneNode;
	}

	return nullptr;
}

GibEngine::Scene::Node* GibEngine::MeshService::GeneratePlane(unsigned int length, unsigned int width, int intervalSize, Mesh::Flags flags)
{
	assert(intervalSize > 0);

	const int widthEnd = width / intervalSize;
	const int lengthEnd = length / intervalSize;

	std::vector<Vertex> vertices;
	std::vector<glm::vec3> positions;

	for (unsigned int x = 0; x < width; x += intervalSize)
	{
		for (unsigned int y = 0; y < length; y += intervalSize)
		{
			if (y == 0)
			{
				positions.push_back(glm::vec3(x, 0, y));
				positions.push_back(glm::vec3(x, 0, length));
			}

			positions.push_back(glm::vec3(x, 0, y));
			positions.push_back(glm::vec3(width, 0, y));
		}
	}

	positions.push_back(glm::vec3(widthEnd, 0, lengthEnd));
	positions.push_back(glm::vec3(0, 0, lengthEnd));
	positions.push_back(glm::vec3(widthEnd, 0, lengthEnd));
	positions.push_back(glm::vec3(widthEnd, 0, 0));

	Vertex v;
	for (auto position : positions)
	{
		v = {};
		v.Position = position;
		vertices.push_back(v);
	}

	Mesh* planeMesh = new Mesh("Plane", nullptr, vertices);

	// Just gotta make sure you've explicitly set the right flags here:
	flags ^= (Mesh::Flags::RENDER_ARRAYS ^ Mesh::Flags::RENDER_FORWARD ^ Mesh::Flags::RENDER_WIREFRAME);
	flags &= ~Mesh::Flags::RENDER_DEFERRED;

	planeMesh->SetFlags(flags);

	Scene::Node* planeNode = new Scene::Node("Plane");
	planeNode->SetEntity(planeMesh);

	return planeNode;
}
