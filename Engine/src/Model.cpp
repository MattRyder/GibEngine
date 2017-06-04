#include "Model.h"

GibEngine::Model::Model() : Entity(EntityType::MODEL)
{
}

GibEngine::Model::Model(const char* modelFilename) : Model()
{
    modelFile = File::GetModelFile(modelFilename);
    LoadModel(modelFile);
}

GibEngine::Model::~Model()
{
}

void GibEngine::Model::ProcessNode(aiNode * node, const aiScene * scene)
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

void GibEngine::Model::LoadModel(File *modelFile)
{
    Assimp::Importer importer;
    const char *modelFilePath = modelFile->GetPath();
    const aiScene *scene = importer.ReadFile(modelFile->GetPath(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Logger::Instance->error("Failed to find Model: {}", importer.GetErrorString());
        return;
    }

    ProcessNode(scene->mRootNode, scene);
    importer.FreeScene();
}

void GibEngine::Model::Render(GLuint shaderProgram, float deltaTime)
{
	for (auto mesh : this->meshes)
	{
		mesh->Render(shaderProgram, 1, deltaTime);
	}
	//this->LoadMaterialUBO(this->materials[0]);
	//glBindVertexArray(VAO);
	//glDrawElementsInstanced(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0, modelInstanceMatrices.size());
}

void GibEngine::Model::UpdateInstances()
{
	for (auto mesh : meshes)
	{
		mesh->UpdateInstances();
	}
}

void GibEngine::Model::AddInstance(glm::mat4 modelMatrix)
{
	for (auto mesh : meshes)
	{
		mesh->AddInstance(modelMatrix);
	}
	UpdateInstances();
}

void GibEngine::Model::Update(double deltaTime)
{
}

int GibEngine::Model::GetID() const
{
    return 0;
}

std::string& GibEngine::Model::GetName() const
{
    return *Entity::entityName;
}

void GibEngine::Model::UpdateUBO()
{
	for (auto mesh : this->meshes)
	{
		mesh->UpdateUBO();
	}
}
