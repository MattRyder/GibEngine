#include "PointLight.h"

float GibEngine::PointLight::GenerateLightVolumeRadius()
{
	const float C = 1.0;
	float brightestColorComponent = fmaxf(fmaxf(diffuseColor.r, diffuseColor.g), diffuseColor.b);
	return (-linearAtten + sqrt(linearAtten * linearAtten - 4 * quadraticAtten * (C - (256.0f / 5.0f) * brightestColorComponent))) / (2.0f / quadraticAtten);

	//float quadraticComp = 4.0f * quadraticAtten + (2.0 - (256.0 / 5.0) * brightestColorComponent);
	//float linearComp = sqrtf(pow(linearAtten, 2) - quadraticComp);
	//return -linearAtten + linearComp;
}

GibEngine::PointLight::PointLight(glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float linearAttenuation, float quadraticAttenuation)
	: LightBase(EntityType::POINT_LIGHT, position, ambientColor, diffuseColor, specularColor)
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
}

void GibEngine::PointLight::SetQuadraticAttenuation(float attenuation)
{
	this->quadraticAtten = attenuation;
}
