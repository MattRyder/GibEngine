#include "scene/VisibleSet.h"

GibEngine::Scene::VisibleSet::VisibleSet(const std::shared_ptr<CameraBase> camera, const std::shared_ptr<GibEngine::Scene::Node> rootSceneNode)
	: camera(camera),
	rootSceneNode(rootSceneNode),
	skyboxNode(),
	meshInstances(std::shared_ptr<MeshInstanceMap>(new MeshInstanceMap())) { }

void GibEngine::Scene::VisibleSet::AddLight(const Scene::Node& lightNode)
{
	lights.push_back(lightNode);
}

void GibEngine::Scene::VisibleSet::AddMeshInstance(const Scene::Node& meshNode)
{
	auto mesh = reinterpret_cast<Mesh*>(meshNode.GetEntity());
	
	auto meshIter = meshInstances->find(mesh);
	if (meshIter != meshInstances->end())
	{
		meshInstances->at(mesh).push_back(meshNode.GetWorldTransform());
	}
	else
	{
		meshInstances->insert(std::pair<const Mesh*, std::vector<glm::mat4>>(mesh, { meshNode.GetWorldTransform() }));
	}
}

void GibEngine::Scene::VisibleSet::ParseNode(const Scene::Node node)
{

	// Sort this entity into it's appropriate set/object:
	if (node.GetEntity() != nullptr)
	{
		switch (node.GetEntity()->GetType())
		{
		case Entity::Type::SKYBOX:
			skyboxNode = node;
			break;
		case Entity::Type::MESH:
			AddMeshInstance(node);
			break;
		case Entity::Type::POINT_LIGHT:
			AddLight(node);
			break;
		default:
			break;
		}
	}

	for (auto iter = node.GetChildNodesBegin(); iter != node.GetChildNodesEnd(); ++iter)
	{
		ParseNode(**iter);
	}
}

std::shared_ptr<GibEngine::CameraBase> GibEngine::Scene::VisibleSet::GetCamera() const
{
	return camera;
}

const GibEngine::Scene::Node GibEngine::Scene::VisibleSet::GetSkyboxNode() const
{
	return skyboxNode;
}

std::vector<GibEngine::Scene::Node> GibEngine::Scene::VisibleSet::GetLights() const
{
	return lights;
}

void GibEngine::Scene::VisibleSet::SetRootSceneNode(const std::shared_ptr<Scene::Node> rootSceneNode)
{
	this->rootSceneNode = rootSceneNode;
}

std::shared_ptr<GibEngine::Scene::VisibleSet::MeshInstanceMap> GibEngine::Scene::VisibleSet::GetMeshInstanceMap() const
{
	return meshInstances;
}

void GibEngine::Scene::VisibleSet::Parse()
{
	meshInstances->clear();
	lights.clear();
	ParseNode(*rootSceneNode);
}
