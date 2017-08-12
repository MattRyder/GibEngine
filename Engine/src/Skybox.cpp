#include "Skybox.h"

GibEngine::Skybox::Skybox(std::string skyboxTextureName, std::string skyboxTextureExtension) : Mesh(skyboxVertices, SKYBOX_VERTICES_COUNT)
{
	this->modelMatrix = glm::mat4();
	this->SetName(&skyboxTextureName);

	std::string skyboxTextureDir = *File::GetSkyboxPath(skyboxTextureName.c_str());
	std::string skyboxFront = skyboxTextureDir + "\\front." + skyboxTextureExtension;
	std::string skyboxBack = skyboxTextureDir + "\\back." + skyboxTextureExtension;
	std::string skyboxLeft = skyboxTextureDir + "\\left." + skyboxTextureExtension;
	std::string skyboxRight = skyboxTextureDir + "\\right." + skyboxTextureExtension;
	std::string skyboxTop = skyboxTextureDir + "\\top." + skyboxTextureExtension;
	std::string skyboxBottom = skyboxTextureDir + "\\bottom." + skyboxTextureExtension;

	skyboxCubemap = new Texture();
	skyboxCubemap->LoadCubemap(skyboxTop, skyboxBottom, skyboxLeft, skyboxRight, skyboxFront, skyboxBack);
}

GibEngine::Skybox::~Skybox() { }

GibEngine::Texture* GibEngine::Skybox::GetCubemap()
{
	return skyboxCubemap;
}

glm::mat4 GibEngine::Skybox::GetModelMatrix()
{
	return modelMatrix;
}

void GibEngine::Skybox::SetModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

void GibEngine::Skybox::Update(double deltaTime)
{
	modelMatrix = glm::rotate(modelMatrix, float(glm::radians(SKYBOX_MOVE_SPEED * deltaTime)), glm::vec3(0, 1, 0));
}