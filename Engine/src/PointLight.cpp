#include "PointLight.h"

float GibEngine::PointLight::GenerateLightVolumeRadius()
{
	float brightestColorComponent = fmaxf(fmaxf(diffuseColor.r, diffuseColor.g), diffuseColor.b);
	float quadraticComp = 4.0f * quadraticAtten + (2.0 - (256.0 / 5.0) * brightestColorComponent);
	float linearComp = sqrtf(pow(linearAtten, 2) - quadraticComp);
	return -linearAtten + linearComp;
}

GibEngine::PointLight::PointLight(glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float linearAttenuation, float quadraticAttenuation)
	: LightBase(EntityType::POINT_LIGHT, position, ambientColor, diffuseColor, specularColor)
{
	this->linearAtten = linearAttenuation;
	this->quadraticAtten = quadraticAttenuation;
	this->lightVolumeRadius = GenerateLightVolumeRadius();
}