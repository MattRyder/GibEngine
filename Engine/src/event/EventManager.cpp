#include "event/EventManager.h"
#include "Logger.h"

void GibEngine::Event::EventManager::AddEventListener(Event::Type type, BaseEntity const* source, EventHandler eventHandler)
{
	auto listener = EventListener(eventHandler);

	listeners[type].insert(std::make_pair(source, eventHandler));
}

void GibEngine::Event::EventManager::ResumeListener(BaseEntity const* source, Event::Type eventType)
{
	if (listeners.count(eventType) == 0)
	{
		return;
	}

	auto listenersForEvent = listeners.at(eventType);
	auto listener = listenersForEvent.find(source);

	listeners[eventType][source].active = true;
}

void GibEngine::Event::EventManager::PauseListener(BaseEntity const* source, Event::Type eventType)
{
	if (listeners.count(eventType) == 0)
	{
		return;
	}

	auto listenersForEvent = listeners.at(eventType);
	auto listener = listenersForEvent.find(source);

	listeners[eventType][source].active = false;
}

void GibEngine::Event::EventManager::Raise(std::shared_ptr<IEvent> event)
{
	if (event->GetType() != Type::ON_TICK)
	{
		//Logger::Instance->info("Event Raised: {}", event->GetName());
	}

	//std::lock_guard<std::mutex> queueLock(eventQueueMutex);
	eventQueue.push(event);
}

void GibEngine::Event::EventManager::Poll(const float deltaTime)
{
	//std::lock_guard<std::mutex> queueLock(eventQueueMutex);

	Raise(std::make_shared<Event::OnTickEvent>());

	while (!eventQueue.empty())
	{
		std::shared_ptr<IEvent> event = eventQueue.front();
		eventQueue.pop();

		if (listeners.count(event->GetType()))
		{
			for (const auto& entityEventHandler : listeners.at(event->GetType()))
			{
				auto listener = entityEventHandler.second;	
				if (listener.active)
				{
					std::bind(listener.handlerFunc, deltaTime, event)();
				}
			}
		}
	}
}