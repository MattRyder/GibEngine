#include "components/Dock.h"

GibEditor::Components::Dock::Dock(std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem, std::shared_ptr<GibEngine::Scene::Node> rootSceneNode, std::shared_ptr<GibEngine::Renderer::Pipeline> pipeline)
	: rootSceneNode(rootSceneNode), pipeline(pipeline)
{

	cbrowser = new Components::ContentBrowser(fileSystem, rootSceneNode, pipeline);
}

void GibEditor::Components::Dock::Render()
{
	ImGui::BeginDockspace();

	ImGui::SetNextDock(ImGuiDockSlot_Left);

	if (ImGui::BeginDock("Game"))
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

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
	if (entityInspector != nullptr)
	{
		ImGui::SetNextDock(ImGuiDockSlot_Right);

		if (ImGui::BeginDock("Inspector"))
		{
			if (ImGui::IsWindowHovered())
			{
				selectedDock = Dock::Type::ENTITY_INSPECTOR;
			}

			entityInspector->Render();

			ImGui::EndDock();
		}
	}


	ImGui::SetNextDock(ImGuiDockSlot_Left);

	if (ImGui::BeginDock("Scene Explorer"))
	{
		if (ImGui::IsWindowHovered())
		{
			selectedDock = Dock::Type::SCENE_TREE;
		}

		if (rootSceneNode != nullptr)
		{
			RenderSceneTreeNode(rootSceneNode.get());
		}

		ImGui::EndDock();

		ImGui::SetNextDock(ImGuiDockSlot_Bottom);

		if (ImGui::BeginDock("Content Explorer", (bool*)0, ImGuiWindowFlags_MenuBar))
		{
			cbrowser->Render();

			ImGui::EndDock();
		}
	}

	ImGui::PopStyleVar();
	ImGui::EndDockspace();
}

GibEditor::Components::Dock::Type GibEditor::Components::Dock::GetSelectedDock() const
{
	return selectedDock;
}

void GibEditor::Components::Dock::RenderSceneTreeNode(GibEngine::Scene::Node* node)
{
	auto nodeName = node->GetName();
	GibEngine::Scene::Node* selectedNode = entityInspector != nullptr ? entityInspector->GetNode() : nullptr;
	GibEngine::Entity* nodeEntity = node->GetEntity();

	if (node->GetChildNodeCount() == 0)
	{
		if (ImGui::Selectable(nodeName.c_str()))
		{
			delete entityInspector;
			entityInspector = new Components::EntityInspector(node);
		}
	}
	else if (GibEngine::Scene::Node::FlagMask(node->GetFlags() & GibEngine::Scene::Node::Flags::MESH_ROOT))
	{
		auto meshPtr = reinterpret_cast<GibEngine::Mesh*>((*node->GetChildNodesBegin())->GetEntity());
		auto meshName = node->GetName() + ": " + meshPtr->GetName();
		if (ImGui::Selectable(meshName.c_str()))
		{
			delete entityInspector;
			entityInspector = new Components::EntityInspector(node);
		}
	}
	else
	{
		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen ^ ImGuiTreeNodeFlags_Bullet ^ ImGuiTreeNodeFlags_Leaf;
		if (ImGui::TreeNodeEx(nodeName.c_str(), treeNodeFlags))
		{
			if (ImGui::IsItemClicked())
			{
				delete entityInspector;
				entityInspector = new Components::EntityInspector(node);
			}

			for (auto iter = node->GetChildNodesBegin(); iter != node->GetChildNodesEnd(); ++iter)
			{
				RenderSceneTreeNode(*iter);
			}

			ImGui::TreePop();
		}
	}
}