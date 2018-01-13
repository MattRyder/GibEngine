#pragma once

#include "scene/Node.h"
#include "CameraBase.h"
#include "PointLight.h"
#include "Skybox.h"

namespace GibEngine
{
	namespace Scene
	{
		class VisibleSet
		{
			const Node* rootSceneNode;
			const Node* skyboxNode;
			
			CameraBase* camera;
			std::map<Mesh*, std::vector<glm::mat4>> meshInstances;
			std::vector<const Scene::Node*> lights;

			void AddLight(const Scene::Node* lightNode);
			void AddMeshInstance(const Scene::Node* meshNode);
			void ParseNode(const Scene::Node* node);

		public:
			VisibleSet(CameraBase* camera, Node* rootSceneNode);

			CameraBase* GetCamera() const;
			const Scene::Node* GetSkyboxNode() const;
			std::vector<const Scene::Node*> GetLights() const;

			std::map<Mesh*, std::vector<glm::mat4>> GetMeshInstanceMap() const;
		};
	}
}