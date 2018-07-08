#include "event/BaseEvent.h"

namespace GibEngine
{
	namespace Event
	{
		class MouseMoveEvent : public BaseEvent
		{
		public:
			const glm::vec2 Movement;
			MouseMoveEvent(const glm::vec2 movement) : BaseEvent(Type::MOUSE_MOVE), Movement(movement) {}
		};

		class MouseButtonDownEvent : public BaseEvent
		{
		public:
			const int Button;

			MouseButtonDownEvent(const int button) : BaseEvent(Type::MOUSE_BUTTON_DOWN), Button(button) { }
		};

		class MouseButtonUpEvent : public BaseEvent
		{
		public:
			const int Button;

			MouseButtonUpEvent(const int button) : BaseEvent(Type::MOUSE_BUTTON_UP), Button(button) { }
		};

		class ScrollEvent : public BaseEvent
		{
		public:
			const glm::vec2 Offset;

			ScrollEvent(const glm::vec2 offset) : BaseEvent(Type::SCROLL), Offset(offset) { }
		};

		class KeyDownEvent : public BaseEvent
		{
		public:
			const int KeyCode;
			const int ScanCode;

			KeyDownEvent(const int keyCode, const int scanCode) 
				: BaseEvent(Event::Type::KEY_DOWN), KeyCode(keyCode), ScanCode(scanCode) { }
		};

		class KeyUpEvent : public BaseEvent
		{
		public:
			const int KeyCode;
			const int ScanCode;

			KeyUpEvent(const int keyCode, const int scanCode)
				: BaseEvent(Event::Type::KEY_UP), KeyCode(keyCode), ScanCode(scanCode) { }
		};
	}
}