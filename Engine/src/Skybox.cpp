#include "Skybox.h"

GibEngine::Skybox::Skybox(std::shared_ptr<Mesh> cubeMesh, const std::shared_ptr<Texture> cubemap)
	: BaseEntity(BaseEntity::Type::SKYBOX, "GE_SKYBOX__DEFAULT_NAME"), cubeMesh(cubeMesh), skyboxCubemap(cubemap), angle(0) { }

GibEngine::Skybox::~Skybox() { }

std::shared_ptr<GibEngine::MeshUploadTicket> GibEngine::Skybox::GetMeshUploadTicket() const
{
	return cubeMesh->GetMeshUploadTicket();
}

std::shared_ptr<GibEngine::Texture> GibEngine::Skybox::GetTexture() const
{
	return skyboxCubemap;
}

void GibEngine::Skybox::RegisterEvents(Event::EventManager* const eventManager)
{
	eventManager->AddEventListener(Event::Type::ON_TICK, this, [this](float deltaTime, std::shared_ptr<Event::IEvent> e)
	{
		auto ote = std::dynamic_pointer_cast<Event::OnTickEvent>(e);
		OnTick(deltaTime, *ote);
	});
}

void GibEngine::Skybox::OnTick(float deltaTime, Event::OnTickEvent & e)
{
	const float MOVE_SPEED = 0.0005f;

	angle += MOVE_SPEED * deltaTime;
	RotateY(glm::radians(angle));
}