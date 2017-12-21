#pragma once 

#include "LightBase.h"

namespace GibEngine
{
	class PointLight : public LightBase
	{
		float linearAtten, quadraticAtten, lightVolumeRadius;

		float GenerateLightVolumeRadius();

	public:
		PointLight();
		PointLight(glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor,
			float linearAttenuation, float quadraticAttenuation);

		float GetLinearAttenuation() const;
		float GetQuadraticAttenuation() const;
		float GetVolumeRadius() const;

		void SetLinearAttenuation(float attenuation);
		void SetQuadraticAttenuation(float attenuation);
	};
}