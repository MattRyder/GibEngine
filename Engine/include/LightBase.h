#pragma once

#include "BaseEntity.h"

namespace GibEngine
{
	class LightBase : public BaseEntity
	{
	protected:
		glm::vec3 ambientColor, diffuseColor, specularColor;

	public:
		LightBase(BaseEntity::Type lightType, glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor);

		glm::vec3 GetAmbientColor() const;
		glm::vec3 GetDiffuseColor() const;
		glm::vec3 GetSpecularColor() const;

		void SetAmbientColor(glm::vec3 color);
		void SetDiffuseColor(glm::vec3 color);
		void SetSpecularColor(glm::vec3 color);
	};
}