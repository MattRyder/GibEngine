#include "Skybox.h"

GibEngine::Skybox::Skybox(const char* skyboxTextureName, const char* skyboxTextureExtension) : Mesh(skyboxTextureName)
{
	this->entityType = EntityType::SKYBOX;

	this->textureExtension = skyboxTextureExtension;

	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i < SKYBOX_VERTICES_COUNT; i += 3)
	{
		GibEngine::Vertex vertex = {};
		vertex.Position = glm::vec3(skyboxVertices[i], skyboxVertices[i + 1], skyboxVertices[i + 2]);
		vertices.push_back(vertex);
	}
	this->SetVertices(vertices);

	LoadCubemap();

}

GibEngine::Skybox::~Skybox()
{
	delete skyboxCubemap;
}

void GibEngine::Skybox::LoadCubemap()
{
	std::string* skyboxTextureDir = File::GetSkyboxPath(entityName);
	skyboxCubemap = Texture::LoadCubemap(skyboxTextureDir, "png");
}

GibEngine::Texture* GibEngine::Skybox::GetCubemap()
{
	return skyboxCubemap;
}

const char* GibEngine::Skybox::GetExtension()
{
	return this->textureExtension;
}

void GibEngine::Skybox::Update(double deltaTime)
{
	//auto skyboxInstance = skyboxModelInstance->GetEntity();
	//skyboxInstance->SetMatrix(glm::rotate(skyboxInstance->GetMatrix(), float(glm::radians(SKYBOX_MOVE_SPEED * deltaTime)), glm::vec3(0, 1, 0)));
}