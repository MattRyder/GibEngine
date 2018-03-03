#include "../include/Mesh.h"

GibEngine::Mesh::Mesh(std::string name, std::shared_ptr<MeshUploadTicket> uploadTicket, std::shared_ptr<Material> material)
	: Entity(Entity::Type::MESH, name), uploadTicket(uploadTicket), material(material), flags(Flags::RENDER_ENABLED) { }

const json11::Json& GibEngine::Mesh::GetGenerationData() const
{

	return generationData;
}

std::shared_ptr<GibEngine::Material> GibEngine::Mesh::GetMaterial() const
{
	return this->material;
}

std::shared_ptr<GibEngine::MeshUploadTicket> GibEngine::Mesh::GetMeshUploadTicket() const
{
	return this->uploadTicket;
}

GibEngine::Mesh::Flags GibEngine::Mesh::GetFlags() const
{
	return flags;
}

void GibEngine::Mesh::Update(double deltaTime) { }

bool GibEngine::Mesh::IsUploaded()
{
	return this->uploadTicket != nullptr;
}

void GibEngine::Mesh::SetFlags(Flags flags)
{
	this->flags = flags;
}

void GibEngine::Mesh::SetGenerationData(json11::Json generationData)
{
	this->generationData = generationData;
}
