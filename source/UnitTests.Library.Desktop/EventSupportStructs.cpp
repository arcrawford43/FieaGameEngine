#include "pch.h"
#include "EventSupportStructs.h"
#include "Foo.h"
#include "GameState.h"

using namespace FieaGameEngine;

namespace UnitTests
{
	void FooSubscriber::Notify(const FieaGameEngine::EventPublisher& eventPublisher)
	{
		const Event<Foo>* fooEvent = eventPublisher.As<Event<Foo>>();
		if (fooEvent != nullptr)
		{
			Data = fooEvent->Message().Data();
			WasNotified = true;
		}
		++Count;
	}

	void EventEnqueueSubscriber::Notify(const FieaGameEngine::EventPublisher& eventPublisher)
	{
		const Event<FooSubscriber>* fooEvent = eventPublisher.As<Event<FooSubscriber>>();
		assert(fooEvent);
		auto sharedEvent = std::make_shared<Event<FooSubscriber>>(fooEvent->Message());
		GameTime gameTime;
		GameState::QueueEvents.Enqueue(sharedEvent, gameTime);
		++Count;
	}

	void EventClearSubscriber::Notify(const FieaGameEngine::EventPublisher& /*eventPublisher*/)
	{
		GameState::QueueEvents.Clear();
		++Count;
	}
}