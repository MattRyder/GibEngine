#pragma once

#include "IComponent.h"

namespace GibEditor
{
	namespace Components
	{
		class StatusBar : public IComponent
		{
		public:
			void Render() override;
		};
	}
}