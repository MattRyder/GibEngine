#pragma once

#include <functional>
#include <imgui.h>

namespace GibEditor
{
	namespace Components
	{
		class IComponent
		{
		public:
			virtual void Render() = 0;
		};
	}
}