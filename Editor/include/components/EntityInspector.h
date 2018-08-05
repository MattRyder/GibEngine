#pragma once

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/string_cast.hpp>

#include "imgui_dock.h"

#include "IComponent.h"
#include "BaseEntity.h"
#include "PointLight.h"
#include "Skybox.h"
#include "FreeCamera.h"

namespace GibEditor
{
	namespace Components
	{
		class EntityInspector : public IComponent
		{
		public:
			EntityInspector() { }

			void SetEntity(std::shared_ptr<GibEngine::BaseEntity> entity)
			{
				this->entity = entity;
			}

			void Render()
			{
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(25, 25));

				if (entity)
				{
					ImGui::Text("Name: %s", entity->GetName().c_str());
					ImGui::Text("Type: %s", entity->GetTypeName().c_str());
					ImGui::Text("GibEngine Entity UID: %s", entity->GetNameKey().c_str());
					RenderTransformNode();
					//ImGui::Dummy(ImVec2(ImGui::GetWindowSize().x, 30));

					if (entity)
					{
						switch (entity->GetType())
						{
						case GibEngine::BaseEntity::Type::CAMERA:
							RenderCamera();
							break;
						case GibEngine::BaseEntity::Type::MESH:
							RenderMesh();
							break;
						case GibEngine::BaseEntity::Type::POINT_LIGHT:
							RenderLight();
							break;
						case GibEngine::BaseEntity::Type::SKYBOX:
							RenderSkybox();
							break;
						}
					}
				}

				ImGui::PopStyleVar();
			}

		private:
			const float INCREMENT_SLOWEST	= 0.001f;
			const float INCREMENT_SLOW		= 0.100f;
			const float INCREMENT_MID		= 0.500f;
			const float INCREMENT_FAST		= 1.000f;

			const ImVec4 colorSuccess = ImVec4(0.439f, 0.972f, 0.227f, 1.0f);
			const ImVec4 colorWarn = ImVec4(0.972f, 0.862f, 0.227f, 1.0f);
			const ImVec4 colorDanger = ImVec4(0.972f, 0.227f, 0.227f, 1.0f);
			const ImVec4 colorPrimary = ImVec4(0.509, 0.780, 0.972, 1.0f);

			std::shared_ptr<GibEngine::BaseEntity> entity;
			bool sceneNodeIsDirty = false;
			bool entityIsDirty = false;

			void RenderTransformNode();
			void RenderCamera();
			void RenderMesh();
			void RenderLight();
			void RenderSkybox();
		};

		inline void EntityInspector::RenderTransformNode()
		{
			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			glm::vec3 pos = entity->GetLocalTransform().GetPosition();
			glm::quat rot = glm::quat();//entity->GetRotation();
			glm::vec3 scale = entity->GetLocalTransform().GetScale();

			if (ImGui::DragFloat3("Position", glm::value_ptr(pos), INCREMENT_SLOW, -1000.0f, 1000.0f))
			{
				auto localTrans = entity->GetLocalTransform();
				localTrans.SetPosition(pos);
				entity->SetLocalTransform(localTrans.GetTransformMatrix());
			}

			if (ImGui::DragFloat("Rotation Y", &rot.y, INCREMENT_SLOWEST, 0, 0.1))
			{
				entity->RotateY(rot.y);
			}

			if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), INCREMENT_SLOW, -1000.0f, 1000.0f))
			{
				auto localTrans = entity->GetLocalTransform();
				localTrans.Scale(scale);
				entity->SetLocalTransform(localTrans.GetTransformMatrix());
			}
		}

		inline void EntityInspector::RenderCamera()
		{
			auto freeCamera = std::dynamic_pointer_cast<GibEngine::FreeCamera>(entity);

			auto label = fmt::format("{} tracking Parent", freeCamera->FlagMask(freeCamera->GetFlags() & GibEngine::FreeCamera::Flags::TRACKING) ? "Stop" : "Start");
			if (ImGui::Button(label.c_str()))
			{
				freeCamera->ToggleTrackingParent();
			}
		}

		inline void EntityInspector::RenderMesh()
		{
			auto mesh = std::dynamic_pointer_cast<GibEngine::Mesh>(entity);
		}

		inline void EntityInspector::RenderLight()
		{
			auto light = std::dynamic_pointer_cast<GibEngine::PointLight>(entity);

			ImGui::Text((std::string("Light ID: ") + std::to_string(light->GetID())).c_str());
			ImGui::Text((std::string("Type: ") + light->GetTypeName()).c_str());

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			float linearAttenuation = light->GetLinearAttenuation();
			if (ImGui::DragFloat("Linear Attenuation", &linearAttenuation, INCREMENT_SLOW, -50.0f, 50.0f))
			{
				light->SetLinearAttenuation(linearAttenuation);
			}

			float quadAttenuation = light->GetQuadraticAttenuation();
			if (ImGui::DragFloat("Quadratic Attenuation", &quadAttenuation, INCREMENT_SLOW, -50.0f, 50.0f))
			{
				light->SetQuadraticAttenuation(quadAttenuation);
			}

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			glm::vec3 amb = light->GetAmbientColor();
			if (ImGui::ColorEdit3("Ambient", glm::value_ptr(amb)))
			{
				light->SetAmbientColor(amb);
			}

			glm::vec3 diff = light->GetDiffuseColor();
			if (ImGui::ColorEdit3("Diffuse", glm::value_ptr(diff)))
			{
				light->SetDiffuseColor(diff);
			}

			glm::vec3 spec = light->GetSpecularColor();
			if (ImGui::ColorEdit3("Specular", glm::value_ptr(spec)))
			{
				light->SetSpecularColor(spec);
			}
		}

		inline void EntityInspector::RenderSkybox()
		{
			auto skybox = std::dynamic_pointer_cast<GibEngine::Skybox>(entity);

			const size_t SKYBOX_INPUT_LEN = 128;
			char skyboxNameBuf[SKYBOX_INPUT_LEN] = { 0 };
			char skyboxTextureExt[SKYBOX_INPUT_LEN] = { 0 };

			memcpy(skyboxNameBuf, skybox->GetName().c_str(), SKYBOX_INPUT_LEN);
			//memcpy(skyboxTextureExt, skybox->GetExtension().c_str(), SKYBOX_INPUT_LEN);

			if (ImGui::InputText("Skybox Name", skyboxNameBuf, SKYBOX_INPUT_LEN))
			{
				skybox->SetName(strdup(skyboxNameBuf));
				//sceneNode->ModifyEntity();
			}

			if (ImGui::InputText("Extension", skyboxTextureExt, SKYBOX_INPUT_LEN))
			{
			}

			if (ImGui::Button("Load Skybox"))
			{
				//skybox->LoadCubemap();
			}
		}
	}
}