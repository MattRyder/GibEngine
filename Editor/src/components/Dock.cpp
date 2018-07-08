#include "components/Dock.h"

GibEditor::Components::Dock::Dock(
	std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem,
	std::shared_ptr<GibEngine::Renderer::API::IGraphicsApi> graphicsApi,
	std::shared_ptr<GibEngine::BaseEntity> rootEntity)
	: rootEntity(rootEntity), graphicsApi(graphicsApi), cbrowser(fileSystem, graphicsApi, rootEntity)
{
	entityInspector = std::make_shared<Components::EntityInspector>();
}

void GibEditor::Components::Dock::Render(unsigned int gameWorldTextureId)
{
	ImGui::BeginDockspace();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
	ImGui::SetNextDock(ImGuiDockSlot_Right);
	if (ImGui::BeginDock("Info"))
	{
		if (ImGui::IsWindowHovered())
		{
			selectedDock = Dock::Type::ENTITY_INSPECTOR;
		}

		//ImGui::ShowStyleEditor(&ImGui::GetStyle());

		entityInspector->Render();

		ImGui::EndDock();
	}
	ImGui::PopStyleVar();


	ImGui::SetNextDock(ImGuiDockSlot_Left);
	if (ImGui::BeginDock("Game"))
	{
		ImVec2 windowSize = ImGui::GetWindowSize();

		if (ImGui::IsWindowHovered())
		{
			selectedDock = Dock::Type::GAME;
		}

		ImGui::Image((void*)gameWorldTextureId, windowSize, ImVec2(0, 1), ImVec2(1, 0));
	
		ImGui::EndDock();
	}
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
	ImGui::SetNextDock(ImGuiDockSlot_Left);
	if (ImGui::BeginDock("Scene Outline"))
	{
		if (ImGui::IsWindowHovered())
		{
			selectedDock = Dock::Type::SCENE_TREE;
		}

		if (rootEntity)
		{
			// Render Scene Outline table header
			ImGui::Columns(2);
			ImGui::Text("Name");
			ImGui::NextColumn();
			ImGui::Text("Type");
			ImGui::Columns(1);

			RenderSceneTree(rootEntity);
		}

		ImGui::EndDock();

		//ImGui::SetNextDock(ImGuiDockSlot_Bottom);

		//if (ImGui::BeginDock("Content Explorer", (bool*)0, ImGuiWindowFlags_MenuBar))
		//{
		//	cbrowser.Render();

		//	ImGui::EndDock();
		//}
	}
	ImGui::PopStyleVar();



	ImGui::EndDockspace();
}

GibEditor::Components::Dock::Type GibEditor::Components::Dock::GetSelectedDock() const
{
	return selectedDock;
}

void GibEditor::Components::Dock::RenderSceneTree(const std::shared_ptr<GibEngine::BaseEntity>& entity)
{
	auto isSelected = selectedSceneOutlineItem == entity->GetNameKey();
	auto entityName = entity->GetName();

	ImGui::Columns(2, NULL, false);
	if (ImGui::Selectable(entityName.c_str(), isSelected))
	{
		selectedSceneOutlineItem = entity->GetNameKey();

		// Show entity in Details pane
		entityInspector->SetEntity(entity);
	}
	ImGui::NextColumn();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7, 0.7, 0.7, 1.0));
	ImGui::Text("%s", entity->GetTypeName().c_str());
	ImGui::PopStyleColor();
	ImGui::Columns(1);

	for (auto iter = entity->ChildrenBegin(); iter != entity->ChildrenEnd(); ++iter)
	{
		if (entity->GetType() == GibEngine::BaseEntity::Type::MESH && iter->get()->GetType() == GibEngine::BaseEntity::Type::MESH)
		{
			continue;
		}

		RenderSceneTree(*iter);
	}
}