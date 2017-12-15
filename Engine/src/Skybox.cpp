#include "Skybox.h"

GibEngine::Skybox::Skybox(const char* skyboxTextureName, const char* skyboxTextureExtension) : Mesh()
{
	this->SetName(skyboxTextureName);
	this->textureExtension = skyboxTextureExtension;

	skyboxModelInstance = new World::DatabaseEntity<Mesh::Instance>(0, new Mesh::Instance(glm::mat4()));
	AddInstance(skyboxModelInstance);

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

GibEngine::Skybox::~Skybox()
{
	delete skyboxCubemap;
}

GibEngine::Texture* GibEngine::Skybox::GetCubemap()
{
	return skyboxCubemap;
}

GibEngine::World::DatabaseEntity<GibEngine::Mesh::Instance>* GibEngine::Skybox::GetMeshInstance()
{
	return this->skyboxModelInstance;
}

const char* GibEngine::Skybox::GetExtension()
{
	return this->textureExtension;
}

void GibEngine::Skybox::Update(double deltaTime)
{
	auto skyboxInstance = skyboxModelInstance->GetEntity();
	skyboxInstance->SetMatrix(glm::rotate(skyboxInstance->GetMatrix(), float(glm::radians(SKYBOX_MOVE_SPEED * deltaTime)), glm::vec3(0, 1, 0)));
}