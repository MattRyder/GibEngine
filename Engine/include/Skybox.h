#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"

namespace GibEngine
{
	class Skybox : public Entity
	{
		const Mesh* cubeMesh;
		std::shared_ptr<Texture> skyboxCubemap;

	public:
		Skybox(const Mesh* cubeMesh, const std::shared_ptr<Texture> cubemap);
		~Skybox();

		const MeshUploadTicket GetMeshUploadTicket() const;
		std::shared_ptr<Texture> GetTexture() const;

		virtual void Update(double deltaTime) override;
	};
}