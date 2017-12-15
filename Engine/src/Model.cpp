#include "Model.h"

GibEngine::Model::Model() : Entity(EntityType::MODEL)
{
	this->modelFile = nullptr;
}

GibEngine::Model::Model(const char* modelFilename) : Model()
{
	this->assetName = strdup(modelFilename);
    modelFile = File::GetModelFile(modelFilename);

	this->SetName(this->assetName);
    LoadModel(modelFile);
}

GibEngine::Model::Model(Mesh* mesh) : Model()
{
	this->meshes.push_back(mesh);
}

GibEngine::Model::~Model()
{
	for (auto mesh : meshes)
	{
		delete mesh;
	}
	meshes.clear();

	delete modelFile;
}

void GibEngine::Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(new Mesh(modelFile->GetDirectory(), mesh, scene));
	}

	//Then process all the child nodes:
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void GibEngine::Model::LoadModel(File* modelFile)
{
    Assimp::Importer importer;
    const char* modelFilePath = modelFile->GetPath();
    const aiScene* scene = importer.ReadFile(modelFile->GetPath(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Logger::Instance->error("Failed to find Model: {}", importer.GetErrorString());
        return;
    }

    ProcessNode(scene->mRootNode, scene);
	importer.FreeScene();
}

void GibEngine::Model::AddInstance(GibEngine::World::DatabaseEntity<GibEngine::Mesh::Instance>* instanceMatrix)
{
	for (Mesh* mesh : this->meshes)
	{
		mesh->AddInstance(instanceMatrix);
	}
}

void GibEngine::Model::Update(double deltaTime)
{
	for (Mesh* mesh : meshes)
	{
		mesh->Update(deltaTime);
	}
}

void GibEngine::Model::UpdateInstance(unsigned int index, GibEngine::World::DatabaseEntity<GibEngine::Mesh::Instance>* instanceMatrix)
{
	for (auto mesh : meshes)
	{
		mesh->UpdateInstance(index, instanceMatrix);
	}
}

void GibEngine::Model::DeleteInstance(World::DatabaseEntity<Mesh::Instance>* modelMatrix)
{
	for (auto mesh : meshes)
	{
		mesh->DeleteInstance(modelMatrix);
	}
}

int GibEngine::Model::GetID() const
{
	return Entity::GetID();
}

const char* GibEngine::Model::GetName() const
{
	return Entity::GetName();
}

const char* GibEngine::Model::GetAssetName() const
{
	return assetName;
}

std::vector<GibEngine::Mesh*> GibEngine::Model::GetMeshes()
{
	return meshes;
}

std::vector<GibEngine::World::DatabaseEntity<GibEngine::Mesh::Instance>*> GibEngine::Model::GetModelInstances() const
{
	if (meshes.size() == 0)
	{
		return std::vector<World::DatabaseEntity<Mesh::Instance>*>();
	}

	return meshes.at(0)->GetInstanceMatrices();
}

void GibEngine::Model::SetWireframeMode(bool wireframeOn)
{
	for (auto mesh : meshes)
	{
		Mesh::Flags f = static_cast<Mesh::Flags>(mesh->GetFlags() ^ (wireframeOn ? Mesh::Flags::RENDER_WIREFRAME : ~Mesh::Flags::RENDER_WIREFRAME));
		mesh->SetFlags(f);
	}
}

void GibEngine::Model::SetShouldRender(bool shouldRender)
{
	for (auto mesh : GetMeshes())
	{
		Mesh::Flags f = static_cast<Mesh::Flags>(mesh->GetFlags() ^ (shouldRender ? Mesh::Flags::RENDER_ENABLED : ~Mesh::Flags::RENDER_ENABLED));
		mesh->SetFlags(f);
	}
}
