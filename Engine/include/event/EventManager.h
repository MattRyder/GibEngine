#pragma once

#include <queue>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <map>

#include "event/BaseEvent.h"
#include "event/OnTickEvent.h"

namespace GibEngine
{
	class BaseEntity;

	namespace Event
	{
		typedef std::function<void(float deltaTime, std::shared_ptr<GibEngine::Event::IEvent>)>  EventHandler;

		struct EventListener
		{
			bool active;
			EventHandler handlerFunc;

			EventListener() : EventListener(nullptr) { }
			EventListener(EventHandler handlerFunc) : active(true), handlerFunc(handlerFunc) {}
		};

		class EventManager
		{
			std::mutex eventQueueMutex;
			std::queue<std::shared_ptr<IEvent>> eventQueue;
			std::map<Event::Type, std::map<BaseEntity const*, EventListener>> listeners;

		public:
			void AddEventListener(Event::Type type, BaseEntity const* source, EventHandler eventHandler);
			void ResumeListener(BaseEntity const* source, Event::Type eventType);
			void PauseListener(BaseEntity const* source, Event::Type eventType);

			void Raise(std::shared_ptr<IEvent> event);
			void Poll(const float deltaTime);
		};
	}
}