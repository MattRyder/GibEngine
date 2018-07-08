#include "MeshService.h"
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define BENCHMARK(FUNC) {\
auto clock = std::chrono::high_resolution_clock::now();\
FUNC;\
auto clockEnd = std::chrono::high_resolution_clock::now();\
auto time = std::chrono::duration_cast<std::chrono::milliseconds>(clockEnd - clock).count();\
Logger::Instance->info("BENCHMARK TIME: {}ms", time);\
}

const float GibEngine::MeshService::CUBE_VERTEX_DATA[CUBE_VERTEX_DATA_SIZE] = {
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

const json11::Json GibEngine::MeshService::CUBE_GENERATION_JSON = json11::Json::object
{
	{ "MeshType", "Cube" },
	{ "MeshFlags", json11::Json::array{ "RENDER_ENABLED" } }
};

void GibEngine::MeshService::ProcessNode(
	const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, 
	const std::string& meshFilePath, 
	std::shared_ptr<BaseEntity> parent, 
	const aiScene& scene, 
	Mesh::Flags flags, 
	aiNode& node)
{
	// Load each mesh for this node:
	for (unsigned int i = 0; i < node.mNumMeshes; i++)
	{
		unsigned int meshIndex = node.mMeshes[i];
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		const aiMesh* mesh = scene.mMeshes[meshIndex];
		const std::string name = mesh->mName.C_Str();
		const aiMaterial* material = scene.mMaterials[mesh->mMaterialIndex];
		const aiMatrix4x4 t = node.mTransformation;
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
				const aiVector3D& tangent = mesh->mTangents[i];
				const aiVector3D& bitangent = mesh->mBitangents[i];
				const aiVector3D& normal = mesh->mNormals[i];

				vertex.Tangent = glm::vec3(tangent.x, tangent.y, tangent.z);
				vertex.Bitangent = glm::vec3(bitangent.x, bitangent.y, bitangent.z);
				vertex.Normal = glm::vec3(normal.x, normal.y, normal.z);
				//float det = dot(cross(vertex.Normal, vertex.Tangent), vertex.Bitangent);
				//vertex.Determinant = (det < 0.0f) ? -1.0f : 1.0f;
			}

			const aiVector3D& pos = mesh->mVertices[i];
			vertex.Position = glm::vec3(pos.x, pos.y, pos.z);

			if (mesh->mTextureCoords[0])
			{
				const aiVector3D& texCoord = mesh->mTextureCoords[0][i];
				vertex.TexCoord = glm::vec2(texCoord.x, texCoord.y);
			}

			vertices.push_back(vertex);
		}
		
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		auto meshDirectory = meshFilePath.substr(0, meshFilePath.find_last_of('/') + 1);
		auto mat = LoadMaterial(graphicsApi, *material, meshDirectory);

		auto meshUploadTicket = graphicsApi->UploadMesh(vertices, indices);

		vertices.clear();
		indices.clear();

		auto meshEntity = std::shared_ptr<Mesh>(new Mesh(name, meshUploadTicket, mat));
		meshEntity->SetFlags(flags);

		parent->AddChild(meshEntity);
	}

	for (unsigned int i = 0; i < node.mNumChildren; i++)
	{
		ProcessNode(graphicsApi, meshFilePath, parent, scene, flags, *node.mChildren[i]);
	}
}

std::shared_ptr<GibEngine::Material> GibEngine::MeshService::LoadMaterial(const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, const aiMaterial& assimpMaterial, const std::string& materialTextureDirectoryPath)
{
	const std::map<aiTextureType, TextureType> textureTypeMap =
	{
		{ aiTextureType_DIFFUSE, TextureType::DIFFUSE },
		{ aiTextureType_HEIGHT, TextureType::NORMAL },
		{ aiTextureType_NORMALS, TextureType::NORMAL },
		{ aiTextureType_SPECULAR, TextureType::SPECULAR }
	};

	std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());

	aiColor3D amb, diff, spec;
	float opacity;
	int shine;

	assimpMaterial.Get(AI_MATKEY_COLOR_SPECULAR, spec);
	assimpMaterial.Get(AI_MATKEY_COLOR_DIFFUSE, diff);
	assimpMaterial.Get(AI_MATKEY_COLOR_AMBIENT, amb);
	assimpMaterial.Get(AI_MATKEY_SHININESS, shine);
	assimpMaterial.Get(AI_MATKEY_OPACITY, opacity);

	material->AmbientColor = glm::vec3(amb.r, amb.g, amb.b);
	material->DiffuseColor = glm::vec3(diff.r, diff.g, diff.b);
	material->SpecularColor = glm::vec3(spec.r, spec.g, spec.b);
	material->Opacity = opacity;
	material->Shininess = shine;

	std::vector<std::future<std::shared_ptr<TextureData>>> textureLoadOperations;

	auto loadTextureAsync = [](const TextureType type, const std::string& textureFilePath)
	{
		auto textureData = std::shared_ptr<TextureData>(new TextureData);
		textureData->Type = type;
		textureData->DataType = StorageType::UNSIGNED_CHAR; // I've invented a meta type-system, remove ASAP.
		textureData->Data = stbi_load(textureFilePath.c_str(), &textureData->Width, &textureData->Height, &textureData->Channels, 0);
		return textureData;
	};

	 //Load Textures
	for (const auto& texturePair : textureTypeMap)
	{
		for (auto i = 0U; i < assimpMaterial.GetTextureCount(texturePair.first); i++)
		{
			aiString str;
			assimpMaterial.GetTexture(texturePair.first, i, &str);

			auto textureFilePath = materialTextureDirectoryPath + str.C_Str();
			textureLoadOperations.push_back(std::async(loadTextureAsync, texturePair.second, textureFilePath));
		}
	}

	for (auto& texFuture : textureLoadOperations)
	{
		unsigned int textureId = 0;
		auto textureData = texFuture.get();

		graphicsApi->UploadTexture2D(&textureId, *textureData, Renderer::API::SamplerFiltering::NEAREST, Renderer::API::SamplerEdgeClamping::REPEAT);

		free(textureData->Data);
		//stbi_image_free(textureData->Data);
		textureData->Data = nullptr;

		auto matTex = MaterialTexture();
		matTex.texture = std::shared_ptr<Texture>(new Texture(textureId, textureData->Type, glm::vec2(textureData->Width, textureData->Height)));

		material->Textures.push_back(matTex);
	}

	return material;
}

std::shared_ptr<GibEngine::Texture> GibEngine::MeshService::LoadCubemap(const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, const std::string& skyboxAbsolutePathWithName, const std::string& extension)
{
	const std::vector<std::string> cubeSides = { "left", "right", "bottom", "top", "front", "back" };

	std::vector<TextureData> textureDataVec;
	auto textureData = TextureData();
	unsigned int textureId = 0;

	for (int i = 0; i < 6; i++)
	{
		textureData = TextureData();
		auto sideFilePath = skyboxAbsolutePathWithName + "/" + cubeSides[i] + "." + extension;

		textureData.Data = stbi_load(sideFilePath.c_str(), &textureData.Width, &textureData.Height, &textureData.Channels, 0);
		textureDataVec.push_back(textureData);
	}
	
	graphicsApi->UploadTextureCubemap(&textureId, textureDataVec);

	for (auto texData : textureDataVec)
	{
		free(texData.Data);
	}

	auto cubemapTexture = std::shared_ptr<Texture>(new Texture(textureId, TextureType::DIFFUSE, glm::vec2(0, 0)));

	return cubemapTexture;
}

GibEngine::Mesh::Flags GibEngine::MeshService::ParseFlagsJson(const std::vector<json11::Json> renderFlagsJsonArray)
{
	Mesh::Flags flags = Mesh::Flags::RENDER_ENABLED;

	for (auto renderFlagStr : renderFlagsJsonArray)
	{
		auto flagStrValue = renderFlagStr.string_value();
		if (flagStrValue.compare("RENDER_WIREFRAME") == 0)
		{
			flags |= Mesh::Flags::RENDER_WIREFRAME;
		}
		else if (flagStrValue.compare("RENDER_DEFERRED") == 0)
		{
			flags |= Mesh::Flags::RENDER_DEFERRED;
		}
		else if (flagStrValue.compare("RENDER_FORWARD") == 0)
		{
			flags |= Mesh::Flags::RENDER_FORWARD;
		}
		else if (flagStrValue.compare("RENDER_ARRAYS") == 0)
		{
			flags |= Mesh::Flags::RENDER_ARRAYS;
		}
	}

	return flags;
}

std::shared_ptr<GibEngine::Mesh> GibEngine::MeshService::Load(const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, const std::string meshFileRelativePath, const json11::Json generationData)
{
	Mesh::Flags genDataMeshFlags = Mesh::Flags::RENDER_ENABLED;

	Assimp::Importer importer;
	const int importerFlags = aiProcess_Triangulate | aiProcess_FlipUVs;
	
	if (generationData != nullptr)
	{
		auto meshFlagsJson = generationData["MeshFlags"].array_items();
		genDataMeshFlags = ParseFlagsJson(meshFlagsJson);
	}

	const aiScene* scene = importer.ReadFile(meshFileRelativePath, importerFlags);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Logger::Instance->error("Failed to load Mesh: {}", importer.GetErrorString());
		return nullptr;
	}

	auto meshFileName = meshFileRelativePath.substr(meshFileRelativePath.find_last_of("/") + 1, meshFileRelativePath.size());
	auto meshRoot = std::shared_ptr<Mesh>(new Mesh("Mesh Root [" + meshFileName + "]"));
	
	// This call needs fixing
	ProcessNode(graphicsApi, meshFileRelativePath, meshRoot, *scene, genDataMeshFlags, *scene->mRootNode);
	meshRoot->SetGenerationData(generationData);

	return meshRoot;
}

std::shared_ptr<GibEngine::Mesh> GibEngine::MeshService::Generate(const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, const json11::Json generationData)
{
	std::string meshType = generationData["MeshType"].string_value();

	auto meshFlagsJson = generationData["MeshFlags"].array_items();
	Mesh::Flags genDataMeshFlags = ParseFlagsJson(meshFlagsJson);
	genDataMeshFlags |= Mesh::Flags::RENDER_ENABLED;

	if (meshType.compare("Plane") == 0)
	{
		Mesh::Flags planeFlagDefaults = Mesh::Flags::RENDER_ARRAYS | Mesh::Flags::RENDER_FORWARD | Mesh::Flags::RENDER_WIREFRAME;

		int length = generationData["Length"].int_value();
		int width = generationData["Width"].int_value();
		int intervalSize = generationData["IntervalSize"].int_value();

		std::vector<Vertex> planeVertices = GeneratePlane(length, width, intervalSize);
		auto meshUploadTicket = graphicsApi->UploadMesh(planeVertices, {});

		auto mesh = std::shared_ptr<Mesh>(new Mesh("PlaneMesh", meshUploadTicket, nullptr));
		mesh->SetGenerationData(generationData);
		mesh->SetFlags(planeFlagDefaults | genDataMeshFlags);

		return mesh;
	}
	else if (meshType.compare("Cube") == 0)
	{
		std::vector<Vertex> vertices;
		for (unsigned int i = 0; i < CUBE_VERTEX_DATA_SIZE; i += 3)
		{
			GibEngine::Vertex vertex = {};
			vertex.Position = glm::vec3(CUBE_VERTEX_DATA[i], CUBE_VERTEX_DATA[i + 1], CUBE_VERTEX_DATA[i + 2]);
			vertices.push_back(vertex);
		}

		auto uploadTicket = graphicsApi->UploadMesh(vertices, {});
		return std::shared_ptr<Mesh>(new Mesh("CubeMesh", uploadTicket, nullptr));
	}

	return nullptr;
}

std::vector<GibEngine::Vertex> GibEngine::MeshService::GeneratePlane(unsigned int length, unsigned int width, int intervalSize)
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

	return vertices;
}
