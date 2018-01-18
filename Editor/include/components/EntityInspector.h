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
					// Render the Database state of the scene node:
					ImGui::Text("Database Record");

					if (sceneNode->GetDatabaseRecord() != nullptr)
					{
						auto dbRec = sceneNode->GetDatabaseRecord();

						switch (dbRec->GetState())
						{
						case GibEngine::World::DatabaseRecord::State::CLEAN:
							ImGui::TextColored(colorSuccess, "Node CLEAN");
							break;
						case GibEngine::World::DatabaseRecord::State::DELETED:
							ImGui::TextColored(colorDanger, "Node DELETED");
							break;
						case GibEngine::World::DatabaseRecord::State::DIRTY:
							ImGui::TextColored(colorWarn, "Node DIRTY");
							break;
						}

						switch (dbRec->GetEntityState())
						{
						case GibEngine::World::DatabaseRecord::State::CLEAN:
							ImGui::TextColored(colorSuccess, "Entity CLEAN");
							break; 
						case GibEngine::World::DatabaseRecord::State::DELETED:
							ImGui::TextColored(colorDanger, "Entity DELETED");
							break;
						case GibEngine::World::DatabaseRecord::State::DIRTY:
							ImGui::TextColored(colorWarn, "Entity DIRTY");
							break;
						}

						ImGui::Dummy(ImVec2(ImGui::GetWindowSize().x, 15));
					}

					RenderTransformNode();
					ImGui::Dummy(ImVec2(ImGui::GetWindowSize().x, 30));


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

			GibEngine::Scene::Node* sceneNode = nullptr;
			bool sceneNodeIsDirty = false;
			bool entityIsDirty = false;

			void RenderTransformNode();
			void RenderMesh();
			void RenderLight();
			void RenderSkybox();
		};

		inline void EntityInspector::RenderTransformNode()
		{
			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			glm::mat4 matrix = sceneNode->GetLocalTransform();
			glm::vec3 pos = glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
			glm::quat rot = sceneNode->GetRotation();
			glm::vec3 scale = glm::vec3(matrix[0][0], matrix[1][1], matrix[2][2]);

			if (ImGui::DragFloat3("Position", glm::value_ptr(pos), INCREMENT_SLOW, -1000.0f, 1000.0f))
			{
				matrix[3] = glm::vec4(pos[0], pos[1], pos[2], 1.0f);
				sceneNode->SetLocalTransform(matrix);
				sceneNode->SetNodeDirty();
			}

			if (ImGui::DragFloat("Rotation Y", &rot.y, INCREMENT_MID, 0, 360))
			{
				sceneNode->RotateY(rot.y);
				sceneNode->SetNodeDirty();
			}

			if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), INCREMENT_SLOW, -1000.0f, 1000.0f))
			{
				matrix[0][0] = scale[0];
				matrix[1][1] = scale[1];
				matrix[2][2] = scale[2];

				sceneNode->SetLocalTransform(matrix);
				sceneNode->SetNodeDirty();
			}
		}

		inline void EntityInspector::RenderMesh()
		{
			GibEngine::Mesh* mesh = reinterpret_cast<GibEngine::Mesh*>(sceneNode->GetEntity());

			ImGui::Text((std::string("Mesh ID: ") + std::to_string(mesh->GetID())).c_str());
			ImGui::Text("Type: Mesh");

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));
		}

		inline void EntityInspector::RenderLight()
		{
			bool setLightDirty = false;
			GibEngine::PointLight* light = reinterpret_cast<GibEngine::PointLight*>(sceneNode->GetEntity());

			ImGui::Text((std::string("Light ID: ") + std::to_string(light->GetID())).c_str());
			ImGui::Text((std::string("Type: ") + light->GetTypeName()).c_str());

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			float linearAttenuation = light->GetLinearAttenuation();
			if (ImGui::DragFloat("Linear Attenuation", &linearAttenuation, INCREMENT_SLOW, 0, 50.0f))
			{
				light->SetLinearAttenuation(linearAttenuation);
				setLightDirty = true;
			}

			float quadAttenuation = light->GetQuadraticAttenuation();
			if (ImGui::DragFloat("Quadratic Attenuation", &quadAttenuation, INCREMENT_SLOW, 0, 50.0f))
			{
				light->SetQuadraticAttenuation(quadAttenuation);
				setLightDirty = true;
			}

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			glm::vec3 amb = light->GetAmbientColor();
			if (ImGui::ColorEdit3("Ambient", glm::value_ptr(amb)))
			{
				light->SetAmbientColor(amb);
				setLightDirty = true;
			}

			glm::vec3 diff = light->GetDiffuseColor();
			if (ImGui::ColorEdit3("Diffuse", glm::value_ptr(diff)))
			{
				light->SetDiffuseColor(diff);
				setLightDirty = true;
			}

			glm::vec3 spec = light->GetSpecularColor();
			if (ImGui::ColorEdit3("Specular", glm::value_ptr(spec)))
			{
				light->SetSpecularColor(spec);
				setLightDirty = true;
			}

			if (setLightDirty)
			{
				sceneNode->ModifyEntity();
			}
		}

		inline void EntityInspector::RenderSkybox()
		{
			GibEngine::Skybox* skybox = reinterpret_cast<GibEngine::Skybox*>(sceneNode->GetEntity());

			const size_t SKYBOX_INPUT_LEN = 128;
			char skyboxNameBuf[SKYBOX_INPUT_LEN] = { 0 };
			char skyboxTextureExt[SKYBOX_INPUT_LEN] = { 0 };

			memcpy(skyboxNameBuf, skybox->GetName(), SKYBOX_INPUT_LEN);
			memcpy(skyboxTextureExt, skybox->GetExtension(), SKYBOX_INPUT_LEN);

			if (ImGui::InputText("Skybox Name", skyboxNameBuf, SKYBOX_INPUT_LEN))
			{
				skybox->SetName(strdup(skyboxNameBuf));
				sceneNode->ModifyEntity();
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