#include "components/Dock.h"

GibEditor::Components::Dock::Dock(GibEngine::Scene::Node* rootSceneNode, GibEngine::Renderer::Pipeline* pipeline)
	: rootSceneNode(rootSceneNode), pipeline(pipeline)
{
	cbrowser = new Components::ContentBrowser(rootSceneNode, pipeline);
}

void GibEditor::Components::Dock::Render()
{
	ImGui::BeginDockspace();

	if (ImGui::BeginDock("Game Name Here"))
	{
		ImVec2 windowSize = ImGui::GetWindowSize();

		if (ImGui::IsWindowHovered())
		{
			selectedDock = Dock::Type::GAME;
		}

		if (pipeline != nullptr)
		{
			ImGui::Image((void*)pipeline->GetFramebuffer()->GetBuffer().textures[GibEngine::Renderer::FramebufferType::RENDER_TO_TEXTURE], windowSize, ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::EndDock();
	}

	ImGui::SetNextDock(ImGuiDockSlot_Left);

	if (ImGui::BeginDock("Scene Explorer"))
	{
		if (ImGui::IsWindowHovered())
		{
			selectedDock = Dock::Type::SCENE_TREE;
		}

		const int COLUMN_COUNT = 3;
		const char* COLUMN_TITLES[COLUMN_COUNT] = { "Name", "Type", "Instance Count" };

		ImGui::Columns(COLUMN_COUNT);

		for (unsigned int i = 0; i < COLUMN_COUNT; i++)
		{
			ImGui::Text("%s", COLUMN_TITLES[i]);
			ImGui::NextColumn();
		}

		//if (rootSceneNode != nullptr)
		//{
		//	for (auto model : level->GetModelEntities())
		//	{
		//		auto modelEntity = model->GetEntity();

		//		bool modelClicked = false;

		//		if (ImGui::Selectable(modelEntity->GetName()))
		//		{
		//			modelClicked = true;
		//		}
		//		ImGui::NextColumn();

		//		if (ImGui::Selectable(modelEntity->GetTypeName()))
		//		{
		//			modelClicked = true;
		//		}
		//		ImGui::NextColumn();

		//		if(ImGui::Selectable(std::to_string(modelEntity->GetModelInstances().size()).c_str()))
		//		{
		//			modelClicked = true;
		//		}
		//		ImGui::NextColumn();

		//		if (modelClicked)
		//		{
		//			delete modelInspector;
		//			modelInspector = new EntityInspector<GibEngine::Model>(model);
		//			activeInspector = ActiveEntityInspector::MODEL;
		//		}
		//	}

		//	for (auto light : level->GetPointLightEntities())
		//	{
		//		auto lightEntity = light->GetEntity();

		//		bool lightSelected = false;

		//		if (ImGui::Selectable(lightEntity->GetName()))
		//		{
		//			lightSelected = true;
		//		}

		//		ImGui::NextColumn();

		//		if (ImGui::Selectable(lightEntity->GetTypeName()))
		//		{
		//			lightSelected = true;
		//		}

		//		if (lightSelected)
		//		{
		//			delete pointLightInspector;
		//			pointLightInspector = new EntityInspector<GibEngine::PointLight>(light);
		//			activeInspector = ActiveEntityInspector::POINT_LIGHT;
		//		}

		//		ImGui::NextColumn();
		//		ImGui::NextColumn();

		//	}

		//	ImGui::Columns(1);
		//}

		ImGui::EndDock();

		ImGui::SetNextDock(ImGuiDockSlot_Bottom);

		if (ImGui::BeginDock("Content Explorer", (bool*)0, ImGuiWindowFlags_MenuBar))
		{
			cbrowser->Render();

			ImGui::EndDock();
		}

		if (activeInspector != ActiveEntityInspector::NONE)
		{
			ImGui::SetNextDock(ImGuiDockSlot_Right);

			if (ImGui::BeginDock("Inspector"))
			{
				if (ImGui::IsWindowHovered())
				{
					selectedDock = Dock::Type::ENTITY_INSPECTOR;
				}

				switch (activeInspector)
				{
				case ActiveEntityInspector::MODEL:
					modelInspector->Render();
					break;
				case ActiveEntityInspector::POINT_LIGHT:
					pointLightInspector->Render();
					break;
				}

				ImGui::EndDock();
			}
		}
	}

	ImGui::EndDockspace();
}

GibEditor::Components::Dock::Type GibEditor::Components::Dock::GetSelectedDock() const
{
	return selectedDock;
}