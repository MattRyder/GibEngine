#include "Skybox.h"

GibEngine::Skybox::Skybox(const Mesh* cubeMesh, const std::shared_ptr<Texture> cubemap)
	: Entity(Entity::Type::SKYBOX, "GE_SKYBOX__DEFAULT_NAME"), cubeMesh(cubeMesh), skyboxCubemap(cubemap)
{ }

GibEngine::Skybox::~Skybox() { }

const GibEngine::MeshUploadTicket GibEngine::Skybox::GetMeshUploadTicket() const
{
	if (cubeMesh != nullptr)
	{
		return *cubeMesh->GetMeshUploadTicket();
	}

	return MeshUploadTicket();
}

std::shared_ptr<GibEngine::Texture> GibEngine::Skybox::GetTexture() const
{
	return skyboxCubemap;
}

void GibEngine::Skybox::Update(double deltaTime)
{
}