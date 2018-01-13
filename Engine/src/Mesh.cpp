#include "../include/Mesh.h"

GibEngine::Mesh::Mesh(const char* name)
	: Entity(EntityType::MESH, name), ownerAssetName(nullptr), flags(Flags::RENDER_ENABLED ^ Flags::RENDER_DEFERRED) { }

GibEngine::Mesh::Mesh(const char* name, const char* ownerFilePath, std::vector<GibEngine::Vertex> vertices, std::vector<unsigned int> indices, std::vector<GibEngine::Material*> material)
	: Entity(EntityType::MESH, name), ownerAssetName(strdup(ownerFilePath)), vertices(vertices), indices(indices), materials(material), flags(Flags::RENDER_ENABLED ^ Flags::RENDER_DEFERRED) { }

GibEngine::Mesh::Mesh(const char* name, const char* ownerFilePath, std::vector<Vertex> vertices)
	: Mesh(name, ownerFilePath, vertices, std::vector<unsigned int>(), std::vector<Material*>()) { }

GibEngine::Mesh::~Mesh()
{
	if (uploadTicket != nullptr)
	{
		uploadTicket->buffers.clear();
	}
	delete uploadTicket;

	vertices.clear();
	std::vector<Vertex>().swap(vertices);
	
	indices.clear();
	std::vector<unsigned int>().swap(indices);

	for (auto material : materials)
	{
		for (auto texture : material->Textures)
		{
			delete texture;
		}

		material->Textures.clear();
		delete material;
	}
	materials.clear();	
}

void GibEngine::Mesh::ProcessMesh(aiMesh *mesh, const aiScene* scene)
{
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
	
	//load materials:
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	Material *mat = new Material();

	aiColor3D amb, diff, spec;
	float opacity;
	int shine;

	material->Get(AI_MATKEY_COLOR_SPECULAR, spec);
	material->Get(AI_MATKEY_COLOR_DIFFUSE, diff);
	material->Get(AI_MATKEY_COLOR_AMBIENT, amb);
	material->Get(AI_MATKEY_SHININESS, shine);
	material->Get(AI_MATKEY_OPACITY, opacity);

	mat->AmbientColor = glm::vec3(amb.r, amb.g, amb.b);
	mat->DiffuseColor = glm::vec3(diff.r, diff.g, diff.b);
	mat->SpecularColor = glm::vec3(spec.r, spec.g, spec.b);
	mat->Opacity = opacity;
	mat->Shininess = shine;

	std::vector<Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
	mat->Textures.insert(mat->Textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	std::vector<Texture*> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
	mat->Textures.insert(mat->Textures.end(), specularMaps.begin(), specularMaps.end());
	//std::vector<Texture*> heightMaps = LoadMaterialTextures(material, aiTextureType_UNKNOWN, TextureType::HEIGHT);
	//mat->Textures.insert(mat->Textures.end(), heightMaps.begin(), heightMaps.end());
	std::vector<Texture*> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::NORMAL);
	mat->Textures.insert(mat->Textures.end(), normalMaps.begin(), normalMaps.end());

	this->materials.push_back(mat);
}

void GibEngine::Mesh::SetIndices(std::vector<unsigned int> indices)
{
	this->indices = indices;
}

void GibEngine::Mesh::SetVertices(std::vector<Vertex> vertices)
{
	this->vertices = vertices;
}

std::vector<GibEngine::Vertex> GibEngine::Mesh::GetVertices() const
{
	return this->vertices;
}

const char* GibEngine::Mesh::GetOwnerAssetName() const
{
	return ownerAssetName;
}

const json11::Json* GibEngine::Mesh::GetGenerationData() const
{
	return generationData;
}

std::vector<unsigned int> GibEngine::Mesh::GetIndices() const
{
	return this->indices;
}

std::vector<GibEngine::Material*> GibEngine::Mesh::GetMaterials() const
{
	return this->materials;
}

GibEngine::MeshUploadTicket* GibEngine::Mesh::GetMeshUploadTicket() const
{
	return this->uploadTicket;
}

GibEngine::Mesh::Flags GibEngine::Mesh::GetFlags() const
{
	return flags;
}

void GibEngine::Mesh::Update(double deltaTime) { }

std::vector<GibEngine::Texture*> GibEngine::Mesh::LoadMaterialTextures(aiMaterial* material, aiTextureType type, GibEngine::TextureType textureType)
{
	std::vector<Texture*> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);

		std::string texturePath = this->ownerAssetName;
		texturePath.substr(texturePath.find_last_of("/") + 1);
		texturePath.append("/").append(str.C_Str());

		Texture* texture = Texture::Load(textureType, &texturePath);
		textures.push_back(texture);
	}
	return textures;

}

bool GibEngine::Mesh::IsUploaded()
{
	return this->uploadTicket != nullptr;
}

void GibEngine::Mesh::SetMeshUploadTicket(MeshUploadTicket *meshUploadReciept)
{
	this->uploadTicket = meshUploadReciept;
}

void GibEngine::Mesh::SetFlags(Flags flags)
{
	this->flags = flags;
}

void GibEngine::Mesh::SetGenerationData(json11::Json* generationData)
{
	this->generationData = generationData;
}
