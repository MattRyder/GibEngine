#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"

namespace GibEngine
{
	class Skybox : public BaseEntity
	{
		std::shared_ptr<Mesh> cubeMesh;
		std::shared_ptr<Texture> skyboxCubemap;
		float angle;

	public:
		Skybox(const std::shared_ptr<Mesh> cubeMesh, const std::shared_ptr<Texture> cubemap);
		~Skybox();

		std::shared_ptr<MeshUploadTicket> GetMeshUploadTicket() const;
		std::shared_ptr<Texture> GetTexture() const;

		virtual void RegisterEvents(Event::EventManager* const eventManager) override;
		virtual void OnTick(float deltaTime, Event::OnTickEvent& e);
	};
}