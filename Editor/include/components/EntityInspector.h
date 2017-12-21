#pragma once

#include <glm/gtx/string_cast.hpp>

#include "imgui_dock.h"

#include "IComponent.h"
#include "Entity.h"
#include "Model.h"
#include "PointLight.h"
#include "world/DatabaseEntity.h"

namespace GibEditor
{
	namespace Components
	{
		template<class T>
		class EntityInspector : public IComponent
		{
		public:
			EntityInspector(GibEngine::World::DatabaseEntity<T>* entity)
			{
				this->entity = entity;
			}

			void Render() { }

		protected:
			struct SelectedInstance
			{
				bool active;
				GibEngine::World::DatabaseEntity<GibEngine::Mesh::Instance>* instance;
				unsigned int index;
			};

		private:
			const float INCREMENT_SLOW = 0.100f;
			const float INCREMENT_MID  = 0.500f;
			const float INCREMENT_FAST = 1.000f;

			GibEngine::World::DatabaseEntity<T>* entity = nullptr;
			SelectedInstance selectedInstance = { 0 };
		};

		template<>
		inline void EntityInspector<GibEngine::Model>::Render()
		{
			GibEngine::Model* model = entity->GetEntity();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(25, 25));

			ImGui::Text((std::string("Entity ID: ") + std::to_string(model->GetID())).c_str());
			ImGui::Text((std::string("Type: ") + model->GetTypeName()).c_str());

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			ImGui::Text((std::string("Instances: ") + std::to_string(model->GetModelInstances().size())).c_str());

			if (ImGui::Button("Add Instance"))
			{
				GibEngine::Mesh::Instance* instance = new GibEngine::Mesh::Instance();
				GibEngine::World::DatabaseEntity<GibEngine::Mesh::Instance>* newInstance = new GibEngine::World::DatabaseEntity<GibEngine::Mesh::Instance>(0, instance);
				newInstance->SetState(GibEngine::World::DatabaseEntityState::NEW);
				model->AddInstance(newInstance);
			}

			for (unsigned int i = 0; i < model->GetModelInstances().size(); i++)
			{
				if (ImGui::Selectable((std::string("Instance #") + std::to_string(i)).c_str()))
				{
					selectedInstance.active = true;
					selectedInstance.index = i;
				}
			}

			if (selectedInstance.active)
			{
				selectedInstance.instance = model->GetModelInstances().at(selectedInstance.index);

				ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

				glm::mat4 matrix = selectedInstance.instance->GetEntity()->GetMatrix();
				glm::vec3 pos = glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
				glm::vec3 rot = glm::vec3();
				glm::vec3 scale = glm::vec3(matrix[0][0], matrix[1][1], matrix[2][2]);

				if (ImGui::DragFloat3("Position", glm::value_ptr(pos), INCREMENT_SLOW, -1000.0f, 1000.0f))
				{
					matrix[3] = glm::vec4(pos[0], pos[1], pos[2], 1.0f);
					selectedInstance.instance->Modify()->SetMatrix(matrix);
					entity->GetEntity()->UpdateInstance(selectedInstance.index, selectedInstance.instance);
				}

				if (ImGui::DragFloat3("Rotation", glm::value_ptr(rot), 1.0f, -1000.0f, 1000.0f))
				{
				}

				if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), INCREMENT_SLOW, -1000.0f, 1000.0f))
				{
					matrix[0][0] = scale[0];
					matrix[1][1] = scale[1];
					matrix[2][2] = scale[2];

					selectedInstance.instance->Modify()->SetMatrix(matrix);
					entity->GetEntity()->UpdateInstance(selectedInstance.index, selectedInstance.instance);
				}
			}

			ImGui::PopStyleVar();
		}

		template<>
		inline void EntityInspector<GibEngine::PointLight>::Render()
		{
			GibEngine::PointLight* light = entity->GetEntity();

			ImGui::Text((std::string("Entity ID: ") + std::to_string(light->GetID())).c_str());
			ImGui::Text((std::string("Type: ") + light->GetTypeName()).c_str());

			ImGui::Dummy(ImVec2(ImGui::GetWindowWidth(), 20));

			glm::vec3 pos = light->GetPosition();
			if (ImGui::DragFloat3("Position", glm::value_ptr(pos), INCREMENT_MID, -1000.0f, 1000.0f))
			{
				entity->Modify()->SetPosition(pos);
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
	}
}