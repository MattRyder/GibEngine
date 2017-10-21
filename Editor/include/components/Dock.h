#pragma once

#include "IComponent.h"
#include "imgui_dock.h"

namespace GibEditor
{
	namespace Components
	{
		class Dock : IComponent
		{
		public:
			virtual void Render() override;
		};
	}
}