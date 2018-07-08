#include "event/BaseEvent.h"

GibEngine::Event::BaseEvent::BaseEvent(Type eventType) : type(eventType) { }

GibEngine::Event::Type GibEngine::Event::BaseEvent::GetType()
{
	return type;
}

std::string GibEngine::Event::BaseEvent::GetName()
{
	return TypeStrings[static_cast<int>(GetType())];
}