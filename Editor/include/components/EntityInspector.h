#pragma once

#include <glm/gtx/string_cast.hpp>

#include "imgui_dock.h"

#include "IComponent.h"
#include "Entity.h"
#include "PointLight.h"
#include "Skybox.h"
#include "scene/Node.h"

namespace GibEditor
{
	namespace Components
	{
		class EntityInspector : public IComponent
		{
		public:
			EntityInspector(GibEngine::Scene::Node* sceneNode)
			{
				this->sceneNode = sceneNode;
			}

			GibEngine::Scene::Node* GetNode() const { return sceneNode; }

			void Render()
			{
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(25, 25));

				if (sceneNode != nullptr)
				{
					if (sceneNode->GetEntity() != nullptr)
					{
						switch (sceneNode->GetEntity()->GetType())
						{
						case GibEngine::EntityType::MESH:
							RenderMesh();
							break;
						case GibEngine::EntityType::POINT_LIGHT:
							RenderLight();
							break;
						case GibEngine::EntityType::SKYBOX:
							RenderSkybox();
							break;
						}
					}
					else
					{
						RenderTransformNode();
					}
				}

				ImGui::PopStyleVar();
			}

		private:
			const float INCREMENT_SLOW = 0.100f;
			const float INCREMENT_MID  = 0.500f;
			const float INCREMENT_FAST = 1.000f;

			GibEngine::Scene::Node* sceneNode = nullptr;

			void RenderTransformNode();
			void RenderMesh();
			void RenderLight();
			void RenderSkybox();
		};

		inline void EntityInspector::RenderTransformNode()
		{
			ImGui::Text("Type: Transform Node");

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			glm::mat4 matrix = sceneNode->GetLocalTransform();
			glm::vec3 pos = glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
			glm::vec3 rot = glm::vec3();
			glm::vec3 scale = glm::vec3(matrix[0][0], matrix[1][1], matrix[2][2]);

			if (ImGui::DragFloat3("Position", glm::value_ptr(pos), INCREMENT_SLOW, -1000.0f, 1000.0f))
			{
				matrix[3] = glm::vec4(pos[0], pos[1], pos[2], 1.0f);
				sceneNode->SetLocalTransform(matrix);
			}

			if (ImGui::DragFloat3("Rotation", glm::value_ptr(rot), 1.0f, -1000.0f, 1000.0f))
			{
			}

			if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), INCREMENT_SLOW, -1000.0f, 1000.0f))
			{
				matrix[0][0] = scale[0];
				matrix[1][1] = scale[1];
				matrix[2][2] = scale[2];

				sceneNode->SetLocalTransform(matrix);
			}
		}

		inline void EntityInspector::RenderMesh()
		{
			GibEngine::Mesh* mesh = reinterpret_cast<GibEngine::Mesh*>(sceneNode->GetEntity());

			ImGui::Text((std::string("Entity ID: ") + std::to_string(mesh->GetID())).c_str());
			ImGui::Text("Type: Mesh");

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			glm::mat4 matrix = sceneNode->GetLocalTransform();
			glm::vec3 pos = glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
			glm::vec3 rot = glm::vec3();
			glm::vec3 scale = glm::vec3(matrix[0][0], matrix[1][1], matrix[2][2]);

			if (ImGui::DragFloat3("Position", glm::value_ptr(pos), INCREMENT_SLOW, -1000.0f, 1000.0f))
			{
				matrix[3] = glm::vec4(pos[0], pos[1], pos[2], 1.0f);
				sceneNode->SetLocalTransform(matrix);
			}

			if (ImGui::DragFloat3("Rotation", glm::value_ptr(rot), 1.0f, -1000.0f, 1000.0f))
			{
			}

			if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), INCREMENT_SLOW, -1000.0f, 1000.0f))
			{
				matrix[0][0] = scale[0];
				matrix[1][1] = scale[1];
				matrix[2][2] = scale[2];

				sceneNode->SetLocalTransform(matrix);
			}
		}

		inline void EntityInspector::RenderLight()
		{
			GibEngine::PointLight* light = reinterpret_cast<GibEngine::PointLight*>(sceneNode->GetEntity());

			ImGui::Text((std::string("Entity ID: ") + std::to_string(light->GetID())).c_str());
			ImGui::Text((std::string("Type: ") + light->GetTypeName()).c_str());

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			glm::mat4 lightTransform = sceneNode->GetLocalTransform();
			glm::vec3 pos = glm::vec3(lightTransform[3][0], lightTransform[3][1], lightTransform[3][2]);
			if (ImGui::DragFloat3("Position", glm::value_ptr(pos), INCREMENT_MID, -1000.0f, 1000.0f))
			{
				lightTransform[3] = glm::vec4(pos, 1.0f);
				sceneNode->SetLocalTransform(lightTransform);
			}

			float linearAttenuation = light->GetLinearAttenuation();
			if (ImGui::DragFloat("Linear Attenuation", &linearAttenuation, INCREMENT_SLOW, 0, 10.0f))
			{
				light->SetLinearAttenuation(linearAttenuation);
			}

			float quadAttenuation = light->GetQuadraticAttenuation();
			if (ImGui::DragFloat("Quadratic Attenuation", &quadAttenuation, INCREMENT_SLOW, 0, 10.0f))
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
			GibEngine::Skybox* skybox = reinterpret_cast<GibEngine::Skybox*>(sceneNode->GetEntity());

			const size_t SKYBOX_INPUT_LEN = 128;
			char skyboxNameBuf[SKYBOX_INPUT_LEN] = { 0 };
			char skyboxTextureExt[SKYBOX_INPUT_LEN] = { 0 };

			memcpy_s(skyboxNameBuf, SKYBOX_INPUT_LEN, skybox->GetName(), strlen(skybox->GetName()));
			memcpy_s(skyboxTextureExt, SKYBOX_INPUT_LEN, skybox->GetExtension(), strlen(skybox->GetExtension()));

			if (ImGui::InputText("Skybox Name", skyboxNameBuf, SKYBOX_INPUT_LEN))
			{
				skybox->SetName(strdup(skyboxNameBuf));
			}

			if (ImGui::InputText("Extension", skyboxTextureExt, SKYBOX_INPUT_LEN))
			{
			}

			if (ImGui::Button("Load Skybox"))
			{
				skybox->LoadCubemap();
			}
		}
	}
}