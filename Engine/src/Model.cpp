﻿#include "Model.h"

GibEngine::Model::Model() : Entity(EntityType::MODEL)
{
	this->modelFile = nullptr;
}

GibEngine::Model::Model(const char* modelFilename) : Model()
{
	this->assetName = modelFilename;
    modelFile = File::GetModelFile(modelFilename);
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
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
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

void GibEngine::Model::AddInstance(glm::mat4 modelMatrix)
{
	for (Mesh* mesh : this->meshes)
	{
		mesh->AddInstance(modelMatrix);
	}
}

void GibEngine::Model::Update(double deltaTime)
{
	for (Mesh* mesh : meshes)
	{
		mesh->Update(deltaTime);
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

std::vector<glm::mat4> GibEngine::Model::GetModelInstances() const
{
	return meshes.at(0)->GetInstanceMatrices();
}