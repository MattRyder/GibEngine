#include "LightBase.h"

GibEngine::LightBase::LightBase(BaseEntity::Type lightType, glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor)
	: BaseEntity(lightType, "LightBase", position), ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor) { }

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

void GibEngine::LightBase::SetAmbientColor(glm::vec3 color)
{
	this->ambientColor = color;
}

void GibEngine::LightBase::SetDiffuseColor(glm::vec3 color)
{
	this->diffuseColor = color;
}

void GibEngine::LightBase::SetSpecularColor(glm::vec3 color)
{
	this->specularColor = color;
}