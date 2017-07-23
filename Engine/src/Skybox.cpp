#include "Skybox.h"

GibEngine::Skybox::Skybox(std::string skyboxTextureName, std::string skyboxTextureExtension) : Mesh(skyboxVertices, 108)
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

GLuint GibEngine::Skybox::GetVAO()
{
	return VAO;
}

GibEngine::Texture* GibEngine::Skybox::GetCubemap()
{
	return skyboxCubemap;
}

glm::mat4 GibEngine::Skybox::GetModelMatrix()
{
	return modelMatrix;
}

void GibEngine::Skybox::Update(double deltaTime)
{
	modelMatrix = glm::rotate(modelMatrix, float(glm::radians(SKYBOX_MOVE_SPEED * deltaTime)), glm::vec3(0, 1, 0));
}