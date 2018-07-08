#pragma once

#include <string>

namespace GibEngine
{
	namespace Event
	{
		enum class Type
		{
			KEY_DOWN,
			KEY_UP,
			ON_TICK,
			MOUSE_BUTTON_DOWN,
			MOUSE_BUTTON_UP,
			MOUSE_MOVE,
			SCROLL,
			TYPE_LAST
		};

		const std::string TypeStrings[static_cast<int>(Type::TYPE_LAST) + 1] =
		{
			"KEY_DOWN", 
			"KEY_UP", 
			"ON_TICK", 
			"MOUSE_BUTTON_DOWN",
			"MOUSE_BUTTON_UP",
			"MOUSE_MOVE", 
			"SCROLL", 
			"TYPE_LAST"
		};

		class IEvent
		{
		public:
			IEvent() {};

			virtual Type GetType() = 0;
			virtual std::string GetName() = 0;
		};
	}
}