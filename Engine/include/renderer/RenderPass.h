#pragma once

#include <map>
#include <vector>

#include "Shader.h"
#include "FreeCamera.h"

namespace GibEngine
{
	namespace Renderer
	{
		/* Map to uniform bindings within the shader */
		enum RenderPassUniform
		{
			PLAYER_CAMERA,
			MATERIAL
		};

		class RenderPass
		{
			bool passEnabled = true;

		protected:
			Shader *shader;
			FreeCamera *camera;
			std::vector<Model *> drawablesList;
			std::map<RenderPassUniform, GLuint> uboIndices;

		public:
			RenderPass(Shader *shader) { this->shader = shader; }

			virtual void Render() = 0;
			virtual void AddDrawable(Model *drawable)
			{
				this->drawablesList.push_back(drawable);
				GLuint materialUBOIndex = glGetUniformBlockIndex(shader->GetShaderId(), "materialUBO");

				if (!drawable->IsUBOCreated())
				{
					drawable->BindUBO(shader->GetShaderId(), materialUBOIndex, RenderPassUniform::MATERIAL);
				}

				uboIndices.insert_or_assign(RenderPassUniform::MATERIAL, materialUBOIndex);
			}

			virtual void SetCameraBase(FreeCamera *camera)
			{
				this->camera = camera;
				GLuint cameraUBOIndex = glGetUniformBlockIndex(shader->GetShaderId(), "cameraUBO");

				if (!camera->IsUBOCreated())
				{
					camera->BindUBO(shader->GetShaderId(), cameraUBOIndex, RenderPassUniform::PLAYER_CAMERA);
				}

				uboIndices.insert_or_assign(RenderPassUniform::PLAYER_CAMERA, cameraUBOIndex);
			}

			void SetPassEnabled(bool value) { this->passEnabled = value; }
		};
	}
}