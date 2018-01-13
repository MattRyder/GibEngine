#include "scene/VisibleSet.h"

void GibEngine::Scene::VisibleSet::AddLight(const Scene::Node* lightNode)
{
	lights.push_back(lightNode);
}

void GibEngine::Scene::VisibleSet::AddMeshInstance(const Scene::Node* meshNode)
{
	auto mesh = reinterpret_cast<Mesh*>(meshNode->GetEntity());
	
	auto meshIter = meshInstances.find(mesh);
	if (meshIter != meshInstances.end())
	{
		meshInstances.at(mesh).push_back(meshNode->GetWorldTransform());
	}
	else
	{
		meshInstances.insert(std::pair<Mesh*, std::vector<glm::mat4>>(mesh, std::vector<glm::mat4>()));
		AddMeshInstance(meshNode);
	}
}

GibEngine::Scene::VisibleSet::VisibleSet(CameraBase* camera, Node* rootSceneNode)
	: camera(camera), rootSceneNode(rootSceneNode) 
{
	ParseNode(rootSceneNode);
}

void GibEngine::Scene::VisibleSet::ParseNode(const Scene::Node* node)
{
	if (node != nullptr)
	{
		// Sort this entity into it's appropriate set/object:
		if (node->GetEntity() != nullptr)
		{
			switch (node->GetEntity()->GetType())
			{
			case EntityType::SKYBOX:
				skyboxNode = node;
				break;
			case EntityType::MESH:
				AddMeshInstance(node);
				break;
			case EntityType::POINT_LIGHT:
				AddLight(node);
				break;
			default:
				break;
			}
		}

		for (auto iter = node->GetChildNodesBegin(); iter != node->GetChildNodesEnd(); ++iter)
		{
			ParseNode(*iter);
		}
	}
}

GibEngine::CameraBase* GibEngine::Scene::VisibleSet::GetCamera() const
{
	return camera;
}

const GibEngine::Scene::Node* GibEngine::Scene::VisibleSet::GetSkyboxNode() const
{
	return skyboxNode;
}

std::vector<const GibEngine::Scene::Node*> GibEngine::Scene::VisibleSet::GetLights() const
{
	return lights;
}

std::map<GibEngine::Mesh*, std::vector<glm::mat4>> GibEngine::Scene::VisibleSet::GetMeshInstanceMap() const
{
	return meshInstances;
}
