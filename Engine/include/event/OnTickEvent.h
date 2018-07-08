#pragma once

#include "event/BaseEvent.h"

namespace GibEngine
{
	namespace Event
	{
		class OnTickEvent : public BaseEvent
		{
		public:
			OnTickEvent() : BaseEvent(Type::ON_TICK) { }
		};
	}
}