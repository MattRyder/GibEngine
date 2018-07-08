// based on https://github.com/nem0/LumixEngine/blob/master/external/imgui/imgui_dock.inl
// modified from https://bitbucket.org/duangle/liminal/src/tip/src/liminal/imgui_dock.cpp

#include "imgui.h"
#define IMGUI_DEFINE_PLACEMENT_NEW
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include "imgui_dock.h"
#include <SimpleIni.h>

using namespace ImGui;

#define nullptr NULL

struct DockContext
{
	enum EndAction_
	{
		EndAction_None,
		EndAction_Panel,
		EndAction_End,
		EndAction_EndChild
	};


	enum Status_
	{
		Status_Docked,
		Status_Float,
		Status_Dragged
	};


	struct Dock
	{
		Dock()
			: id(0)
			, next_tab(nullptr)
			, prev_tab(nullptr)
			, parent(nullptr)
			, pos(0, 0)
			, size(-1, -1)
			, active(true)
			, status(Status_Float)
			, label(nullptr)
			, opened(false)
        
		{
			location[0] = 0;
			children[0] = children[1] = nullptr;
		}


		~Dock() { MemFree(label); }


		ImVec2 getMinSize() const
		{
			if (!children[0]) return ImVec2(16, 16 + GetTextLineHeightWithSpacing());

			ImVec2 s0 = children[0]->getMinSize();
			ImVec2 s1 = children[1]->getMinSize();
			return isHorizontal() ? ImVec2(s0.x + s1.x, ImMax(s0.y, s1.y))
								  : ImVec2(ImMax(s0.x, s1.x), s0.y + s1.y);
		}


		bool isHorizontal() const { return children[0]->pos.x < children[1]->pos.x; }


		void setParent(Dock* dock)
		{
			parent = dock;
			for (Dock* tmp = prev_tab; tmp; tmp = tmp->prev_tab) tmp->parent = dock;
			for (Dock* tmp = next_tab; tmp; tmp = tmp->next_tab) tmp->parent = dock;
		}
        
        Dock& getRoot()
        {
            Dock *dock = this;
            while (dock->parent)
                dock = dock->parent;
            return *dock;
        }


		Dock& getSibling()
		{
			IM_ASSERT(parent);
			if (parent->children[0] == &getFirstTab()) return *parent->children[1];
			return *parent->children[0];
		}


		Dock& getFirstTab()
		{
			Dock* tmp = this;
			while (tmp->prev_tab) tmp = tmp->prev_tab;
			return *tmp;
		}


		void setActive()
		{
			active = true;
			for (Dock* tmp = prev_tab; tmp; tmp = tmp->prev_tab) tmp->active = false;
			for (Dock* tmp = next_tab; tmp; tmp = tmp->next_tab) tmp->active = false;
		}


		bool isContainer() const { return children[0] != nullptr; }


		void setChildrenPosSize(const ImVec2& _pos, const ImVec2& _size)
		{
			ImVec2 s = children[0]->size;
			if (isHorizontal())
			{
				s.y = _size.y;
				s.x = (float)int(
					_size.x * children[0]->size.x / (children[0]->size.x + children[1]->size.x));
				if (s.x < children[0]->getMinSize().x)
				{
					s.x = children[0]->getMinSize().x;
				}
				else if (_size.x - s.x < children[1]->getMinSize().x)
				{
					s.x = _size.x - children[1]->getMinSize().x;
				}
				children[0]->setPosSize(_pos, s);

				s.x = _size.x - children[0]->size.x;
				ImVec2 p = _pos;
				p.x += children[0]->size.x;
				children[1]->setPosSize(p, s);
			}
			else
			{
				s.x = _size.x;
				s.y = (float)int(
					_size.y * children[0]->size.y / (children[0]->size.y + children[1]->size.y));
				if (s.y < children[0]->getMinSize().y)
				{
					s.y = children[0]->getMinSize().y;
				}
				else if (_size.y - s.y < children[1]->getMinSize().y)
				{
					s.y = _size.y - children[1]->getMinSize().y;
				}
				children[0]->setPosSize(_pos, s);

				s.y = _size.y - children[0]->size.y;
				ImVec2 p = _pos;
				p.y += children[0]->size.y;
				children[1]->setPosSize(p, s);
			}
		}


		void setPosSize(const ImVec2& _pos, const ImVec2& _size)
		{
			size = _size;
			pos = _pos;
			for (Dock* tmp = prev_tab; tmp; tmp = tmp->prev_tab)
			{
				tmp->size = _size;
				tmp->pos = _pos;
			}
			for (Dock* tmp = next_tab; tmp; tmp = tmp->next_tab)
			{
				tmp->size = _size;
				tmp->pos = _pos;
			}

			if (!isContainer()) return;
			setChildrenPosSize(_pos, _size);
		}


		char* label;
		ImU32 id;
		Dock* next_tab;
		Dock* prev_tab;
		Dock* children[2];
		Dock* parent;
		bool active;
		ImVec2 pos;
		ImVec2 size;
		Status_ status;
		int last_frame;
		int invalid_frames;
		char location[16];
		bool opened;
		bool first;
	};


	ImVector<Dock*> m_docks;
	ImVec2 m_drag_offset;
	Dock* m_current;
    Dock *m_next_parent;
	int m_last_frame;
	EndAction_ m_end_action;
    ImVec2 m_workspace_pos;
    ImVec2 m_workspace_size;
    ImGuiDockSlot m_next_dock_slot;
    ImVec4 dockBorderColor;


    DockContext()
        : m_current(nullptr)
        , m_next_parent(nullptr)
        , m_last_frame(0)
        , m_next_dock_slot(ImGuiDockSlot_Tab)
        , dockBorderColor(ImVec4(0, 0, 0, 0))
    {
    }


	~DockContext() {}

	Dock& getDock(const char* label, bool opened)
	{
		ImU32 id = ImHash(label, 0);
		for (int i = 0; i < m_docks.size(); ++i)
		{
			if (m_docks[i]->id == id) return *m_docks[i];
		}

		Dock* new_dock = (Dock*)MemAlloc(sizeof(Dock));
		IM_PLACEMENT_NEW(new_dock) Dock();
		m_docks.push_back(new_dock);
		new_dock->label = ImStrdup(label);
		IM_ASSERT(new_dock->label);
		new_dock->id = id;
		new_dock->setActive();
		new_dock->status = (m_docks.size() == 1)?Status_Docked:Status_Float;
		new_dock->pos = ImVec2(0, 0);
		new_dock->size = GetIO().DisplaySize;
		new_dock->opened = opened;
		new_dock->first = true;
		new_dock->last_frame = 0;
		new_dock->invalid_frames = 0;
		new_dock->location[0] = 0;
		return *new_dock;
	}


	void putInBackground()
	{
		ImGuiWindow* win = GetCurrentWindow();
		ImGuiContext& g = *GImGui;
		if (g.Windows[0] == win) return;

		for (int i = 0; i < g.Windows.Size; i++)
		{
			if (g.Windows[i] == win)
			{
				for (int j = i - 1; j >= 0; --j)
				{
					g.Windows[j + 1] = g.Windows[j];
				}
				g.Windows[0] = win;
				break;
			}
		}
	}


	void splits()
	{
		if (GetFrameCount() == m_last_frame) return;
		m_last_frame = GetFrameCount();

		putInBackground();
        
		for (int i = 0; i < m_docks.size(); ++i) {
			Dock& dock = *m_docks[i];
            if (!dock.parent && (dock.status == Status_Docked)) {
                dock.setPosSize(m_workspace_pos, m_workspace_size);
            }
        }

		ImU32 color = GetColorU32(ImGuiCol_Button);
		ImU32 color_hovered = GetColorU32(ImGuiCol_ButtonHovered);
		ImDrawList* draw_list = GetWindowDrawList();
		ImGuiIO& io = GetIO();
		for (int i = 0; i < m_docks.size(); ++i)
		{
			Dock& dock = *m_docks[i];
			if (!dock.isContainer()) continue;

			PushID(i);
			if (!IsMouseDown(0)) dock.status = Status_Docked;
            
            ImVec2 pos0 = dock.children[0]->pos;
            ImVec2 pos1 = dock.children[1]->pos;
            ImVec2 size0 = dock.children[0]->size;
            ImVec2 size1 = dock.children[1]->size;
            
            ImGuiMouseCursor cursor;

			ImVec2 dsize(0, 0);
			ImVec2 min_size0 = dock.children[0]->getMinSize();
			ImVec2 min_size1 = dock.children[1]->getMinSize();
			if (dock.isHorizontal())
			{
                cursor = ImGuiMouseCursor_ResizeEW;
                SetCursorScreenPos(ImVec2(dock.pos.x + size0.x, dock.pos.y));
				InvisibleButton("split", ImVec2(3, dock.size.y));
				if (dock.status == Status_Dragged) dsize.x = io.MouseDelta.x;
				dsize.x = -ImMin(-dsize.x, dock.children[0]->size.x - min_size0.x);
				dsize.x = ImMin(dsize.x, dock.children[1]->size.x - min_size1.x);
                size0 += dsize;
                size1 -= dsize;
                pos0 = dock.pos;
                pos1.x = pos0.x + size0.x;
                pos1.y = dock.pos.y;
                size0.y = size1.y = dock.size.y;
                size1.x = ImMax(min_size1.x, dock.size.x - size0.x);
                size0.x = ImMax(min_size0.x, dock.size.x - size1.x);
			}
			else
			{
                cursor = ImGuiMouseCursor_ResizeNS;
                SetCursorScreenPos(ImVec2(dock.pos.x, dock.pos.y + size0.y));
				InvisibleButton("split", ImVec2(dock.size.x, 3));
				if (dock.status == Status_Dragged) dsize.y = io.MouseDelta.y;
				dsize.y = -ImMin(-dsize.y, dock.children[0]->size.y - min_size0.y);
				dsize.y = ImMin(dsize.y, dock.children[1]->size.y - min_size1.y);
                size0 += dsize;
                size1 -= dsize;
                pos0 = dock.pos;
                pos1.x = dock.pos.x;
                pos1.y = pos0.y + size0.y;
                size0.x = size1.x = dock.size.x;
                size1.y = ImMax(min_size1.y, dock.size.y - size0.y);
                size0.y = ImMax(min_size0.y, dock.size.y - size1.y);
			}
			dock.children[0]->setPosSize(pos0, size0);
			dock.children[1]->setPosSize(pos1, size1);

            if (IsItemHovered()) {
                SetMouseCursor(cursor);
            }
            
			if (IsItemHovered() && IsMouseClicked(0))
			{
				dock.status = Status_Dragged;
			}

			draw_list->AddRectFilled(
				GetItemRectMin(), GetItemRectMax(), IsItemHovered() ? color_hovered : color);
			PopID();
		}
	}


	void checkNonexistent()
	{
		int frame_limit = ImMax(0, ImGui::GetFrameCount() - 2);
		for (int i = 0; i < m_docks.size(); ++i)
		{
			Dock *dock = m_docks[i];
			if (dock->isContainer()) continue;
			if (dock->status == Status_Float) continue;
			if (dock->last_frame < frame_limit)
			{
				++dock->invalid_frames;
				if (dock->invalid_frames > 2)
				{
					doUndock(*dock);
					dock->status = Status_Float;
				}
				return;
			}
			dock->invalid_frames = 0;
		}
	}


	Dock* getDockAt(const ImVec2& pos) const
	{
		for (int i = 0; i < m_docks.size(); ++i)
		{
			Dock& dock = *m_docks[i];
			if (dock.isContainer()) continue;
			if (dock.status != Status_Docked) continue;
			if (IsMouseHoveringRect(dock.pos, dock.pos + dock.size, false))
			{
				return &dock;
			}
		}

		return nullptr;
	}


	static ImRect getDockedRect(const ImRect& rect, ImGuiDockSlot dock_slot)
	{
		ImVec2 half_size = rect.GetSize() * 0.5f;
		switch (dock_slot)
		{
			default: return rect;
			case ImGuiDockSlot_Top: return ImRect(rect.Min, ImVec2(rect.Max.x, rect.Min.y + half_size.y));
			case ImGuiDockSlot_Right: return ImRect(rect.Min + ImVec2(half_size.x, 0), rect.Max);
			case ImGuiDockSlot_Bottom: return ImRect(rect.Min + ImVec2(0, half_size.y), rect.Max);
			case ImGuiDockSlot_Left: return ImRect(rect.Min, ImVec2(rect.Min.x + half_size.x, rect.Max.y));
		}
	}


	static ImRect getSlotRect(ImRect parent_rect, ImGuiDockSlot dock_slot)
	{
		ImVec2 size = parent_rect.Max - parent_rect.Min;
		ImVec2 center = parent_rect.Min + size * 0.5f;
		switch (dock_slot)
		{
			default: return ImRect(center - ImVec2(20, 20), center + ImVec2(20, 20));
			case ImGuiDockSlot_Top: return ImRect(center + ImVec2(-20, -50), center + ImVec2(20, -30));
			case ImGuiDockSlot_Right: return ImRect(center + ImVec2(30, -20), center + ImVec2(50, 20));
			case ImGuiDockSlot_Bottom: return ImRect(center + ImVec2(-20, +30), center + ImVec2(20, 50));
			case ImGuiDockSlot_Left: return ImRect(center + ImVec2(-50, -20), center + ImVec2(-30, 20));
		}
	}


	static ImRect getSlotRectOnBorder(ImRect parent_rect, ImGuiDockSlot dock_slot)
	{
		ImVec2 size = parent_rect.Max - parent_rect.Min;
		ImVec2 center = parent_rect.Min + size * 0.5f;
		switch (dock_slot)
		{
			case ImGuiDockSlot_Top:
				return ImRect(ImVec2(center.x - 20, parent_rect.Min.y + 10),
					ImVec2(center.x + 20, parent_rect.Min.y + 30));
			case ImGuiDockSlot_Left:
				return ImRect(ImVec2(parent_rect.Min.x + 10, center.y - 20),
					ImVec2(parent_rect.Min.x + 30, center.y + 20));
			case ImGuiDockSlot_Bottom:
				return ImRect(ImVec2(center.x - 20, parent_rect.Max.y - 30),
					ImVec2(center.x + 20, parent_rect.Max.y - 10));
			case ImGuiDockSlot_Right:
				return ImRect(ImVec2(parent_rect.Max.x - 30, center.y - 20),
					ImVec2(parent_rect.Max.x - 10, center.y + 20));
			default: IM_ASSERT(false);
		}
		IM_ASSERT(false);
		return ImRect();
	}


	Dock* getRootDock()
	{
		for (int i = 0; i < m_docks.size(); ++i)
		{
			if (!m_docks[i]->parent &&
				(m_docks[i]->status == Status_Docked || m_docks[i]->children[0]))
			{
				return m_docks[i];
			}
		}
		return nullptr;
	}


	bool dockSlots(Dock& dock, Dock* dest_dock, const ImRect& rect, bool on_border)
	{
		ImDrawList* canvas = GetWindowDrawList();
		ImU32 color = GetColorU32(ImGuiCol_Button);
		ImU32 color_hovered = GetColorU32(ImGuiCol_ButtonHovered);
		ImVec2 mouse_pos = GetIO().MousePos;
		for (int i = 0; i < (on_border ? 4 : 5); ++i)
		{
			ImRect r =
				on_border ? getSlotRectOnBorder(rect, (ImGuiDockSlot)i) : getSlotRect(rect, (ImGuiDockSlot)i);
			bool hovered = r.Contains(mouse_pos);
			canvas->AddRectFilled(r.Min, r.Max, hovered ? color_hovered : color);
			if (!hovered) continue;

			if (!IsMouseDown(0))
			{
				doDock(dock, dest_dock ? dest_dock : getRootDock(), (ImGuiDockSlot)i);
				return true;
			}
			ImRect docked_rect = getDockedRect(rect, (ImGuiDockSlot)i);
			canvas->AddRectFilled(docked_rect.Min, docked_rect.Max, GetColorU32(ImGuiCol_Button));
		}
		return false;
	}


	void handleDrag(Dock& dock)
	{
		Dock* dest_dock = getDockAt(GetIO().MousePos);

		Begin("##Overlay",
			NULL,
			ImVec2(0, 0),
			0.f,
			ImGuiWindowFlags_Tooltip | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_AlwaysAutoResize);
		ImDrawList* canvas = GetWindowDrawList();

		canvas->PushClipRectFullScreen();

		ImU32 docked_color = GetColorU32(ImGuiCol_FrameBg);
		docked_color = (docked_color & 0x00ffFFFF) | 0x80000000;
		dock.pos = GetIO().MousePos - m_drag_offset;
		if (dest_dock)
		{
			if (dockSlots(dock,
					dest_dock,
					ImRect(dest_dock->pos, dest_dock->pos + dest_dock->size),
					false))
			{
				canvas->PopClipRect();
				End();
				return;
			}
		}
		if (dockSlots(dock, nullptr, ImRect(m_workspace_pos, m_workspace_pos + m_workspace_size), true))
		{
			canvas->PopClipRect();
			End();
			return;
		}
		canvas->AddRectFilled(dock.pos, dock.pos + dock.size, docked_color);
		canvas->PopClipRect();

		if (!IsMouseDown(0))
		{
			dock.status = Status_Float;
			dock.location[0] = 0;
			dock.setActive();
		}

		End();
	}


	void fillLocation(Dock& dock)
	{
		if (dock.status == Status_Float) return;
		char* c = dock.location;
		Dock* tmp = &dock;
		while (tmp->parent)
		{
			*c = getLocationCode(tmp);
			tmp = tmp->parent;
			++c;
		}
		*c = 0;
	}


	void doUndock(Dock& dock)
	{
		if (dock.prev_tab)
			dock.prev_tab->setActive();
		else if (dock.next_tab)
			dock.next_tab->setActive();
		else
			dock.active = false;
		Dock* container = dock.parent;

		if (container)
		{
			Dock& sibling = dock.getSibling();
			if (container->children[0] == &dock)
			{
				container->children[0] = dock.next_tab;
			}
			else if (container->children[1] == &dock)
			{
				container->children[1] = dock.next_tab;
			}

			bool remove_container = !container->children[0] || !container->children[1];
			if (remove_container)
			{
				if (container->parent)
				{
					Dock*& child = container->parent->children[0] == container
									   ? container->parent->children[0]
									   : container->parent->children[1];
					child = &sibling;
					child->setPosSize(container->pos, container->size);
					child->setParent(container->parent);
				}
				else
				{
					if (container->children[0])
					{
						container->children[0]->setParent(nullptr);
						container->children[0]->setPosSize(container->pos, container->size);
					}
					if (container->children[1])
					{
						container->children[1]->setParent(nullptr);
						container->children[1]->setPosSize(container->pos, container->size);
					}
				}
				for (int i = 0; i < m_docks.size(); ++i)
				{
					if (m_docks[i] == container)
					{
						m_docks.erase(m_docks.begin() + i);
						break;
					}
				}
                if (container == m_next_parent)
                    m_next_parent = nullptr;
				container->~Dock();
				MemFree(container);
			}
		}
		if (dock.prev_tab) dock.prev_tab->next_tab = dock.next_tab;
		if (dock.next_tab) dock.next_tab->prev_tab = dock.prev_tab;
		dock.parent = nullptr;
		dock.prev_tab = dock.next_tab = nullptr;
	}


	void drawTabbarListButton(Dock& dock)
	{
		if (!dock.next_tab) return;

		ImDrawList* draw_list = GetWindowDrawList();
		if (InvisibleButton("list", ImVec2(16, 16)))
		{
			OpenPopup("tab_list_popup");
		}
		if (BeginPopup("tab_list_popup"))
		{
			Dock* tmp = &dock;
			while (tmp)
			{
				bool dummy = false;
				if (Selectable(tmp->label, &dummy))
				{
					tmp->setActive();
                    m_next_parent = tmp;
				}
				tmp = tmp->next_tab;
			}
			EndPopup();
		}

		bool hovered = IsItemHovered();
		ImVec2 min = GetItemRectMin();
		ImVec2 max = GetItemRectMax();
		ImVec2 center = (min + max) * 0.5f;
		ImU32 text_color = GetColorU32(ImGuiCol_Text);
		ImU32 color_active = GetColorU32(ImGuiCol_FrameBgActive);
		draw_list->AddRectFilled(ImVec2(center.x - 4, min.y + 3),
			ImVec2(center.x + 4, min.y + 5),
			hovered ? color_active : text_color);
		draw_list->AddTriangleFilled(ImVec2(center.x - 4, min.y + 7),
			ImVec2(center.x + 4, min.y + 7),
			ImVec2(center.x, min.y + 12),
			hovered ? color_active : text_color);
	}


	bool tabbar(Dock& dock, bool close_button)
	{
		float tabbar_height = 2 * GetTextLineHeightWithSpacing();
		ImVec2 size(dock.size.x, tabbar_height);
		bool tab_closed = false;

		SetCursorScreenPos(dock.pos);
		char tmp[20];
		ImFormatString(tmp, IM_ARRAYSIZE(tmp), "tabs%d", (int)dock.id);
		if (BeginChild(tmp, size, true))
		{
			Dock* dock_tab = &dock;

			ImDrawList* draw_list = GetWindowDrawList();
			ImU32 color = GetColorU32(ImGuiCol_FrameBg);
			ImU32 color_active = GetColorU32(ImGuiCol_FrameBgActive);
			ImU32 color_hovered = GetColorU32(ImGuiCol_FrameBgHovered);
			ImU32 text_color = GetColorU32(ImGuiCol_Text);
			float line_height = GetTextLineHeightWithSpacing();
			float tab_base;

			drawTabbarListButton(dock);

			while (dock_tab)
			{
				SameLine(0, 15);

				const char* text_end = FindRenderedTextEnd(dock_tab->label);
				ImVec2 size(CalcTextSize(dock_tab->label, text_end).x, line_height);
				if (InvisibleButton(dock_tab->label, size))
				{
					dock_tab->setActive();
                    m_next_parent = dock_tab;
				}

				if (IsItemActive() && IsMouseDragging())
				{
					m_drag_offset = GetMousePos() - dock_tab->pos;
					doUndock(*dock_tab);
					dock_tab->status = Status_Dragged;
				}

				bool hovered = IsItemHovered();
				ImVec2 pos = GetItemRectMin();
				if (dock_tab->active && close_button)
				{
					size.x += 16 + GetStyle().ItemSpacing.x;
					SameLine();
					tab_closed = InvisibleButton("close", ImVec2(16, 16));
					ImVec2 center = (GetItemRectMin() + GetItemRectMax()) * 0.5f;
					draw_list->AddLine(
						center + ImVec2(-3.5f, -3.5f), center + ImVec2(3.5f, 3.5f), text_color);
					draw_list->AddLine(
						center + ImVec2(3.5f, -3.5f), center + ImVec2(-3.5f, 3.5f), text_color);
				}
				tab_base = pos.y;
				draw_list->PathClear();
				draw_list->PathLineTo(pos + ImVec2(-15, size.y));
				draw_list->PathBezierCurveTo(
					pos + ImVec2(-10, size.y), pos + ImVec2(-5, 0), pos + ImVec2(0, 0), 10);
				draw_list->PathLineTo(pos + ImVec2(size.x, 0));
				draw_list->PathBezierCurveTo(pos + ImVec2(size.x + 5, 0),
					pos + ImVec2(size.x + 10, size.y),
					pos + ImVec2(size.x + 15, size.y),
					10);
				draw_list->PathFillConvex(
					hovered ? color_hovered : (dock_tab->active ? color_active : color));
				draw_list->AddText(pos + ImVec2(0, 1), text_color, dock_tab->label, text_end);

				dock_tab = dock_tab->next_tab;
			}
			ImVec2 cp(dock.pos.x, tab_base + line_height);
			draw_list->AddLine(cp, cp + ImVec2(dock.size.x, 0), color);
		}
		EndChild();
		return tab_closed;
	}


	static void setDockPosSize(Dock& dest, Dock& dock, ImGuiDockSlot dock_slot, Dock& container)
	{
		IM_ASSERT(!dock.prev_tab && !dock.next_tab && !dock.children[0] && !dock.children[1]);

		dest.pos = container.pos;
		dest.size = container.size;
		dock.pos = container.pos;
		dock.size = container.size;

		switch (dock_slot)
		{
			case ImGuiDockSlot_Bottom:
				dest.size.y *= 0.5f;
				dock.size.y *= 0.5f;
				dock.pos.y += dest.size.y;
				break;
			case ImGuiDockSlot_Right:
				dest.size.x *= 0.5f;
				dock.size.x *= 0.5f;
				dock.pos.x += dest.size.x;
				break;
			case ImGuiDockSlot_Left:
				dest.size.x *= 0.5f;
				dock.size.x *= 0.5f;
				dest.pos.x += dock.size.x;
				break;
			case ImGuiDockSlot_Top:
				dest.size.y *= 0.5f;
				dock.size.y *= 0.5f;
				dest.pos.y += dock.size.y;
				break;
			default: IM_ASSERT(false); break;
		}
		dest.setPosSize(dest.pos, dest.size);

		if (container.children[1]->pos.x < container.children[0]->pos.x ||
			container.children[1]->pos.y < container.children[0]->pos.y)
		{
			Dock* tmp = container.children[0];
			container.children[0] = container.children[1];
			container.children[1] = tmp;
		}
	}


	void doDock(Dock& dock, Dock* dest, ImGuiDockSlot dock_slot)
	{
		IM_ASSERT(!dock.parent);
		if (!dest)
		{
			dock.status = Status_Docked;
			dock.setPosSize(m_workspace_pos, m_workspace_size);
		}
		else if (dock_slot == ImGuiDockSlot_Tab)
		{
			Dock* tmp = dest;
			while (tmp->next_tab)
			{
				tmp = tmp->next_tab;
			}

			tmp->next_tab = &dock;
			dock.prev_tab = tmp;
			dock.size = tmp->size;
			dock.pos = tmp->pos;
			dock.parent = dest->parent;
			dock.status = Status_Docked;
		}
		else if (dock_slot == ImGuiDockSlot_None)
		{
			dock.status = Status_Float;
		}
		else
		{
			Dock* container = (Dock*)MemAlloc(sizeof(Dock));
			IM_PLACEMENT_NEW(container) Dock();
			m_docks.push_back(container);
			container->children[0] = &dest->getFirstTab();
			container->children[1] = &dock;
			container->next_tab = nullptr;
			container->prev_tab = nullptr;
			container->parent = dest->parent;
			container->size = dest->size;
			container->pos = dest->pos;
			container->status = Status_Docked;
			container->label = ImStrdup("");

			if (!dest->parent)
			{
			}
			else if (&dest->getFirstTab() == dest->parent->children[0])
			{
				dest->parent->children[0] = container;
			}
			else
			{
				dest->parent->children[1] = container;
			}

			dest->setParent(container);
			dock.parent = container;
			dock.status = Status_Docked;

			setDockPosSize(*dest, dock, dock_slot, *container);
		}
		dock.setActive();
	}


	void rootDock(const ImVec2& pos, const ImVec2& size)
	{
		Dock* root = getRootDock();
		if (!root) return;

		ImVec2 min_size = root->getMinSize();
		ImVec2 requested_size = size;
		root->setPosSize(pos, ImMax(min_size, requested_size));
	}


	void setDockActive()
	{
		IM_ASSERT(m_current);
		if (m_current) m_current->setActive();
	}


	static ImGuiDockSlot getSlotFromLocationCode(char code)
	{
		switch (code)
		{
			case '1': return ImGuiDockSlot_Left;
			case '2': return ImGuiDockSlot_Top;
			case '3': return ImGuiDockSlot_Bottom;
			default: return ImGuiDockSlot_Right;
		}
	}


	static char getLocationCode(Dock* dock)
	{
		if (!dock) return '0';

		if (dock->parent->isHorizontal())
		{
			if (dock->pos.x < dock->parent->children[0]->pos.x) return '1';
			if (dock->pos.x < dock->parent->children[1]->pos.x) return '1';
			return '0';
		}
		else
		{
			if (dock->pos.y < dock->parent->children[0]->pos.y) return '2';
			if (dock->pos.y < dock->parent->children[1]->pos.y) return '2';
			return '3';
		}
	}


	void tryDockToStoredLocation(Dock& dock)
	{
		if (dock.status == Status_Docked) return;
		if (dock.location[0] == 0) return;
		
		Dock* tmp = getRootDock();
		if (!tmp) return;

		Dock* prev = nullptr;
		char* c = dock.location + strlen(dock.location) - 1;
		while (c >= dock.location && tmp)
		{
			prev = tmp;
			tmp = *c == getLocationCode(tmp->children[0]) ? tmp->children[0] : tmp->children[1];
			if(tmp) --c;
		}
		doDock(dock, tmp ? tmp : prev, tmp ? ImGuiDockSlot_Tab : getSlotFromLocationCode(*c));
	}


	bool begin(const char* label, bool* opened, ImGuiWindowFlags extra_flags)
	{
        ImGuiDockSlot next_slot = m_next_dock_slot;
        m_next_dock_slot = ImGuiDockSlot_Tab;
		Dock& dock = getDock(label, !opened || *opened);
		if (!dock.opened && (!opened || *opened)) tryDockToStoredLocation(dock);
		dock.last_frame = ImGui::GetFrameCount();
		if (strcmp(dock.label, label) != 0)
		{
			MemFree(dock.label);
			dock.label = ImStrdup(label);
		}

		m_end_action = EndAction_None;

        bool prev_opened = dock.opened;
        bool first = dock.first;
		if (dock.first && opened) *opened = dock.opened;
		dock.first = false;
		if (opened && !*opened)
		{
			if (dock.status != Status_Float)
			{
				fillLocation(dock);
				doUndock(dock);
				dock.status = Status_Float;
			}
			dock.opened = false;
			return false;
		}
		dock.opened = true;

		checkNonexistent();
        
        if (first || (prev_opened != dock.opened)) {
            Dock* root = m_next_parent ? m_next_parent : getRootDock();
            if (root && (&dock != root) && !dock.parent) {
                doDock(dock, root, next_slot);
            }
            m_next_parent = &dock;
        }
        
		m_current = &dock;
		if (dock.status == Status_Dragged) handleDrag(dock);

		bool is_float = dock.status == Status_Float;

		if (is_float)
		{
			SetNextWindowPos(dock.pos);
			SetNextWindowSize(dock.size);
			bool ret = Begin(label,
				opened,
				dock.size,
				-1.0f,
				ImGuiWindowFlags_NoCollapse | extra_flags);
			m_end_action = EndAction_End;
			dock.pos = GetWindowPos();
			dock.size = GetWindowSize();

			ImGuiContext& g = *GImGui;

			if (g.ActiveId == GetCurrentWindow()->MoveId && g.IO.MouseDown[0])
			{
				m_drag_offset = GetMousePos() - dock.pos;
				doUndock(dock);
				dock.status = Status_Dragged;
			}
			return ret;
		}

		if (!dock.active && dock.status != Status_Dragged) return false;

        //beginPanel();

		m_end_action = EndAction_EndChild;
        
        splits();


		PushStyleColor(ImGuiCol_Border, dockBorderColor);
		float tabbar_height = GetTextLineHeightWithSpacing();
		if (tabbar(dock.getFirstTab(), false))
		{
			fillLocation(dock);
			*opened = false;
		}
		ImVec2 pos = dock.pos;
		ImVec2 size = dock.size;
		pos.y += tabbar_height + GetStyle().WindowPadding.y;
		size.y -= tabbar_height + GetStyle().WindowPadding.y;

		SetCursorScreenPos(pos);
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
								 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
								 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus |
								 extra_flags;
		bool ret = BeginChild(label, size, true, flags);
		PopStyleColor();
        
		return ret;
	}


	void end()
	{
		m_current = nullptr;
        if (m_end_action != EndAction_None) {
            if (m_end_action == EndAction_End)
            {
                End();
            }
            else if (m_end_action == EndAction_EndChild)
            {
                PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
                EndChild();
                PopStyleColor();
            }
            //endPanel();
        }
	}

  Dock* getDockByIndex(int idx) { return idx >= 0 && idx < m_docks.size() ? m_docks[idx] : nullptr; }

  int getDockIndex(Dock *dock) {
    if (!dock) return -1;

    for (int i = 0; i < m_docks.size(); ++i) {
      if (dock == m_docks[i]) return i;
    }

    IM_ASSERT(false);
    return -1;
  }

  void save() {
    CSimpleIniA ini;
    ini.SetUnicode();

    for (int i = 0; i < m_docks.size(); i++) {
      Dock& dock = *m_docks[i];

      uint64_t addr = (uint64_t)static_cast<void*>(&dock);

      const char* sectionname = std::to_string(addr).c_str();

      ini.SetValue(sectionname, "label", std::string(dock.label).c_str());

      ini.SetValue(sectionname, "index", std::to_string(i).c_str());
      ini.SetValue(sectionname, "x", std::to_string(dock.pos.x).c_str());
      ini.SetValue(sectionname, "y", std::to_string(dock.pos.y).c_str());
      ini.SetValue(sectionname, "status", std::to_string(dock.status).c_str());
      ini.SetValue(sectionname, "size_x", std::to_string(dock.size.x).c_str());
      ini.SetValue(sectionname, "size_y", std::to_string(dock.size.y).c_str());
      ini.SetValue(sectionname, "active", std::to_string(dock.active).c_str());
      ini.SetValue(sectionname, "opened", std::to_string(dock.opened).c_str());

      fillLocation(dock);
      ini.SetValue(sectionname, "location", std::string(dock.location).c_str());

      ini.SetValue(sectionname, "child0", std::to_string(getDockIndex(dock.children[0])).c_str());
      ini.SetValue(sectionname, "child1", std::to_string(getDockIndex(dock.children[1])).c_str());

      ini.SetValue(sectionname, "prevtab", std::to_string(getDockIndex(dock.prev_tab)).c_str());
      ini.SetValue(sectionname, "nexttab", std::to_string(getDockIndex(dock.next_tab)).c_str());

      ini.SetValue(sectionname, "parent", std::to_string(getDockIndex(dock.parent)).c_str());
    }

    ini.SaveFile("editor.ini");
  }

  void load() {
    CSimpleIni ini;
    ini.SetUnicode();
    SI_Error rc = ini.LoadFile("editor.ini");
    if (rc < 0) {
      return;
    }

    CSimpleIniA::TNamesDepend sections;
    ini.GetAllSections(sections);
    CSimpleIniA::TNamesDepend::const_iterator i;

    for (int a = 0; a < m_docks.size(); ++a) {
      m_docks[a]->~Dock();
      MemFree(m_docks[a]);
    }
    m_docks.clear();

    for (i = sections.begin(); i != sections.end(); ++i) {
      Dock *new_dock = (Dock *)MemAlloc(sizeof(Dock));
      m_docks.push_back(new_dock);
    }

    for (i = sections.begin(); i != sections.end(); ++i) {
      Dock *dock;

      int index = atoi(ini.GetValue(i->pItem, "index"));

      dock = getDockByIndex(index);

      //dis dock don't exist yo
      if (dock == nullptr)
        return;

      dock->last_frame = 0;
      dock->invalid_frames = 0;

      if (ini.GetValue(i->pItem, "label") != " ") {
        dock->label = ImStrdup(ini.GetValue(i->pItem, "label"));
        dock->id = ImHash(dock->label, 0);
      }

      dock->pos.x = (float)atof(ini.GetValue(i->pItem, "x"));
      dock->pos.y = (float)atof(ini.GetValue(i->pItem, "y"));
      dock->size.x = (float)atof(ini.GetValue(i->pItem, "size_x"));
      dock->size.y = (float)atof(ini.GetValue(i->pItem, "size_y"));
      dock->status = (Status_)atoi(ini.GetValue(i->pItem, "status"));
      dock->opened = ini.GetBoolValue(i->pItem, "opened");
      dock->active = ini.GetBoolValue(i->pItem, "active");

      strcpy(dock->location, ini.GetValue(i->pItem, "location"));

      const char *child0 = ini.GetValue(i->pItem, "child0");
      dock->children[0] = getDockByIndex(atoi(child0));

      const char *child1 = ini.GetValue(i->pItem, "child1");
      dock->children[1] = getDockByIndex(atoi(child1));

      const char* prevtab = ini.GetValue(i->pItem, "prevtab");
      dock->prev_tab = getDockByIndex(atoi(prevtab));

      const char* nexttab = ini.GetValue(i->pItem, "nexttab");
      dock->next_tab = getDockByIndex(atoi(nexttab));

      const char *parent = ini.GetValue(i->pItem, "parent");
      dock->parent = getDockByIndex(atoi(parent));

      tryDockToStoredLocation(*dock);
    }
  }

  };

static DockContext g_dock;


void ImGui::ShutdownDock()
{
	for (int i = 0; i < g_dock.m_docks.size(); ++i)
	{
		g_dock.m_docks[i]->~Dock();
		MemFree(g_dock.m_docks[i]);
	}
	g_dock.m_docks.clear();
}

void ImGui::SetNextDock(ImGuiDockSlot slot) {
    g_dock.m_next_dock_slot = slot;
}

void ImGui::BeginDockspace() {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar;
    BeginChild("###workspace", ImVec2(0,0), false, flags);
    g_dock.m_workspace_pos = GetWindowPos();
    g_dock.m_workspace_size = GetWindowSize();
}

void ImGui::EndDockspace() {
    EndChild();
}

void ImGui::SetDockActive()
{
	g_dock.setDockActive();
}

IMGUI_API bool ImGui::IsDockDragging() {
  return g_dock.m_current->status == DockContext::Status_Dragged;
}

IMGUI_API void ImGui::SaveDock() {
  g_dock.save();
}

IMGUI_API void ImGui::LoadDock(const char * dockConfigurationIniFilename) {
  g_dock.load();
}

IMGUI_API void ImGui::PushDockBorderColor(ImColor color) {
  g_dock.dockBorderColor = color;
}

IMGUI_API void ImGui::PopDockBorderColor() {
  g_dock.dockBorderColor = ImVec4(0, 0, 0, 0);
}

bool ImGui::BeginDock(const char* label, bool* opened, ImGuiWindowFlags extra_flags)
{
	return g_dock.begin(label, opened, extra_flags);
}


void ImGui::EndDock()
{
	g_dock.end();
}