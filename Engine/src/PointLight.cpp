#include "PointLight.h"

GibEngine::PointLight::PointLight()
	: PointLight(glm::vec3(), glm::vec3(0.2f), glm::vec3(0.7f), glm::vec3(0.9f), 0.0f, 1.8f) { }

GibEngine::PointLight::PointLight(glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float linearAttenuation, float quadraticAttenuation)
	: LightBase(BaseEntity::Type::POINT_LIGHT, position, ambientColor, diffuseColor, specularColor)
{
	this->linearAtten = linearAttenuation;
	this->quadraticAtten = quadraticAttenuation;
	this->lightVolumeRadius = GenerateLightVolumeRadius();
}

float GibEngine::PointLight::GetLinearAttenuation() const
{
	return this->linearAtten;
}

float GibEngine::PointLight::GetQuadraticAttenuation() const
{
	return this->quadraticAtten;
}

float GibEngine::PointLight::GetVolumeRadius() const
{
	return this->lightVolumeRadius;
}

void GibEngine::PointLight::SetLinearAttenuation(float attenuation)
{
	this->linearAtten = attenuation;
	this->lightVolumeRadius = GenerateLightVolumeRadius();
	//Logger::Instance->info("LVR: {}", this->lightVolumeRadius);
}

void GibEngine::PointLight::SetQuadraticAttenuation(float attenuation)
{
	this->quadraticAtten = attenuation;
	this->lightVolumeRadius = GenerateLightVolumeRadius();
	//Logger::Instance->info("LVR: {}", this->lightVolumeRadius);
}

float GibEngine::PointLight::GenerateLightVolumeRadius()
{
	const float C = 1.0;
	float brightestColorComponent = std::fmaxf(std::fmaxf(diffuseColor.r, diffuseColor.g), diffuseColor.b);
	return (-linearAtten + std::sqrt(linearAtten * linearAtten - 4 * quadraticAtten * (C - (256.0f / 5.0f) * brightestColorComponent))) / (2.0f / quadraticAtten);
}