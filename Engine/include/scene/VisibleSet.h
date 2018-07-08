#pragma once

#include "CameraBase.h"
#include "PointLight.h"
#include "Skybox.h"
#include "renderer/api/IGraphicsApi.h"

namespace GibEngine
{
	namespace Scene
	{
		class VisibleSet
		{
			typedef std::map<const std::shared_ptr<Mesh>, std::vector<glm::mat4>> MeshInstanceMap;

			std::shared_ptr<BaseEntity> rootEntity;
			std::shared_ptr<Skybox> skyboxNode;
			
			std::shared_ptr<CameraBase> camera;
			std::shared_ptr<MeshInstanceMap> meshInstances;
			std::vector<std::shared_ptr<LightBase>> lights;

			void AddLight(const std::shared_ptr<LightBase> lightNode);
			void AddMeshInstance(const std::shared_ptr<Mesh> meshNode);

			void ParseNode(const std::shared_ptr<BaseEntity> node);

		public:
			VisibleSet(const std::shared_ptr<CameraBase> camera, const std::shared_ptr<BaseEntity> rootEntity);

			std::shared_ptr<CameraBase> GetCamera() const;
			const std::shared_ptr<Skybox> GetSkyboxNode() const;
			std::vector<std::shared_ptr<LightBase>> GetLights() const;

			void SetRootEntity(const std::shared_ptr<BaseEntity> rootEntity);

			std::shared_ptr<MeshInstanceMap> GetMeshInstanceMap() const;

			void Parse(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi);
		};
	}
}