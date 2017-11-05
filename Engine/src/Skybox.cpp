#include "Skybox.h"

GibEngine::Skybox::Skybox(const char* skyboxTextureName, const char* skyboxTextureExtension) : Mesh()//skyboxVertices, SKYBOX_VERTICES_COUNT)
{
	this->modelMatrix = glm::mat4();
	this->SetName(skyboxTextureName);
	this->textureExtension = skyboxTextureExtension;

	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i < SKYBOX_VERTICES_COUNT; i += 3)
	{
		GibEngine::Vertex vertex = {};
		vertex.Position = glm::vec3(skyboxVertices[i], skyboxVertices[i + 1], skyboxVertices[i + 2]);
		vertices.push_back(vertex);
	}
	this->SetVertices(vertices);

	std::string* skyboxTextureDir = File::GetSkyboxPath(skyboxTextureName);
	skyboxCubemap = Texture::LoadCubemap(skyboxTextureDir, "png");
}

GibEngine::Skybox::~Skybox() { }

GibEngine::Texture* GibEngine::Skybox::GetCubemap()
{
	return skyboxCubemap;
}

glm::mat4 GibEngine::Skybox::GetModelMatrix()
{
	return this->GetInstanceMatrices().size() > 0 ? this->GetInstanceMatrices().at(0) : glm::mat4();
}

void GibEngine::Skybox::SetModelMatrix(glm::mat4 modelMatrix)
{
	this->SetInstance(0, modelMatrix);
}

const char* GibEngine::Skybox::GetExtension()
{
	return this->textureExtension;
}

void GibEngine::Skybox::Update(double deltaTime)
{
	SetModelMatrix(glm::rotate(GetModelMatrix(), float(glm::radians(SKYBOX_MOVE_SPEED * deltaTime)), glm::vec3(0, 1, 0)));
}