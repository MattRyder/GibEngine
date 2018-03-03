#pragma once

#include "scene/Node.h"
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
			typedef std::map<const Mesh*, std::vector<glm::mat4>> MeshInstanceMap;

			const std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi;

			std::shared_ptr<Scene::Node> rootSceneNode;
			Node skyboxNode;
			
			std::shared_ptr<CameraBase> camera;
			std::shared_ptr<MeshInstanceMap> meshInstances;
			std::vector<Scene::Node> lights;

			void AddLight(const Scene::Node& lightNode);
			void AddMeshInstance(const Scene::Node& meshNode);
			void ParseNode(const Scene::Node node);

		public:
			VisibleSet(const std::shared_ptr<CameraBase> camera, const std::shared_ptr<Scene::Node> rootSceneNode);

			std::shared_ptr<CameraBase> GetCamera() const;
			const Scene::Node GetSkyboxNode() const;
			std::vector<Scene::Node> GetLights() const;

			void SetRootSceneNode(const std::shared_ptr<Scene::Node> rootSceneNode);

			std::shared_ptr<MeshInstanceMap> GetMeshInstanceMap() const;

			void Parse();


		};
	}
}