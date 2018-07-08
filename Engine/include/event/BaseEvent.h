#pragma once

#include "IEvent.h"

namespace GibEngine
{
	namespace Event
	{
		class BaseEvent : public IEvent
		{
			Type type;

		public:
			BaseEvent(Type eventType);
			virtual Type GetType() override;
			virtual std::string GetName() override;		
		};
	}
}