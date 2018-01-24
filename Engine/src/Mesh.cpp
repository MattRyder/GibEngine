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
	indices.clear();

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

	// clear the meshes vertex data from the heap
	vertices.clear();
	vertices.shrink_to_fit();
	
	indices.clear();
	indices.shrink_to_fit();
}

void GibEngine::Mesh::SetFlags(Flags flags)
{
	this->flags = flags;
}

void GibEngine::Mesh::SetGenerationData(json11::Json* generationData)
{
	this->generationData = generationData;
}
