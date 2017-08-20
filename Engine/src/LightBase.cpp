#include "LightBase.h"

GibEngine::LightBase::LightBase(EntityType lightType, glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor)
	: Entity(lightType, position)
{
	this->ambientColor = ambientColor;
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
}

glm::vec3 GibEngine::LightBase::GetAmbientColor() const
{
	return this->ambientColor;
}

glm::vec3 GibEngine::LightBase::GetDiffuseColor() const
{
	return this->diffuseColor;
}

glm::vec3 GibEngine::LightBase::GetSpecularColor() const
{
	return this->specularColor;
}