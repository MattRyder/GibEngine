#include "scene/VisibleSet.h"

GibEngine::Scene::VisibleSet::VisibleSet(const std::shared_ptr<CameraBase> camera, const std::shared_ptr<GibEngine::BaseEntity> rootEntity)
	: camera(camera),
	rootEntity(rootEntity),
	skyboxNode(),
	meshInstances(std::shared_ptr<MeshInstanceMap>(new MeshInstanceMap())) { }

void GibEngine::Scene::VisibleSet::AddLight(const std::shared_ptr<LightBase> lightNode)
{
	lights.push_back(lightNode);
}

void GibEngine::Scene::VisibleSet::AddMeshInstance(const std::shared_ptr<Mesh> meshNode)
{
	auto meshIter = meshInstances->find(meshNode);
	if (meshIter != meshInstances->end())
	{
		meshInstances->at(meshNode).push_back(meshNode->GetWorldTransform());
	}
	else
	{
		meshInstances->insert(std::pair<const std::shared_ptr<Mesh>, std::vector<glm::mat4>>(meshNode, { meshNode->GetWorldTransform() }));
	}
}

void GibEngine::Scene::VisibleSet::ParseNode(std::shared_ptr<BaseEntity> node)
{

	// Sort this entity into it's appropriate set/object:
	switch (node->GetType())
	{
	case BaseEntity::Type::SKYBOX:
	{
		auto skyboxEntity = std::dynamic_pointer_cast<Skybox>(node);
		skyboxNode = skyboxEntity;
		break;
	}
	case BaseEntity::Type::MESH:
	{
		auto meshEntity = std::dynamic_pointer_cast<Mesh>(node);
		AddMeshInstance(meshEntity);
		break;
	}
	case BaseEntity::Type::POINT_LIGHT:
	{	auto lightEntity = std::dynamic_pointer_cast<PointLight>(node);
		AddLight(lightEntity);
		break;
	}
	default:
		break;
	}

	for (auto iter = node->ChildrenBegin(); iter != node->ChildrenEnd(); ++iter)
	{
		ParseNode(*iter);
	}
}

std::shared_ptr<GibEngine::CameraBase> GibEngine::Scene::VisibleSet::GetCamera() const
{
	return camera;
}

const std::shared_ptr<GibEngine::Skybox> GibEngine::Scene::VisibleSet::GetSkyboxNode() const
{
	return skyboxNode;
}

std::vector<std::shared_ptr<GibEngine::LightBase>> GibEngine::Scene::VisibleSet::GetLights() const
{
	return lights;
}

void GibEngine::Scene::VisibleSet::SetRootEntity(const std::shared_ptr<GibEngine::BaseEntity> rootEntity)
{
	this->rootEntity = rootEntity;
}

std::shared_ptr<GibEngine::Scene::VisibleSet::MeshInstanceMap> GibEngine::Scene::VisibleSet::GetMeshInstanceMap() const
{
	return meshInstances;
}

void GibEngine::Scene::VisibleSet::Parse(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi)
{
	meshInstances->clear();
	lights.clear();

	if (rootEntity)
	{
		ParseNode(rootEntity);
	}

	for (auto iter = meshInstances->begin(); iter != meshInstances->end(); ++iter)
	{
		const auto mesh = iter->first;
		if (mesh->GetMeshUploadTicket())
		{
			graphicsApi->UpdateMeshInstances(*mesh->GetMeshUploadTicket(), iter->second);
		}
	}
}
