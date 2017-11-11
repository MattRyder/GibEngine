#pragma once

#include "IComponent.h"
#include "imgui_dock.h"

#include "world/World.h"
#include "renderer/Pipeline.h"

namespace GibEditor
{
	namespace Components
	{
		class Dock : IComponent
		{
			GibEngine::World::Level* level;
			GibEngine::Renderer::Pipeline* pipeline;

		public:
			Dock(GibEngine::World::Level* level, GibEngine::Renderer::Pipeline* pipeline);
			virtual void Render() override;
		};
	}
}