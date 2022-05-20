#pragma once
#include "Event.h"
#include "EventQueue.h"
#include "EventSubscriber.h"

namespace UnitTests
{
	struct FooSubscriber : public FieaGameEngine::EventSubscriber
	{
		void Notify(const FieaGameEngine::EventPublisher& eventPublisher) override;

		bool WasNotified{ false };
		size_t Data{ 0 };
		size_t Count{ 0 };
	};

	struct EventEnqueueSubscriber final : public FieaGameEngine::EventSubscriber
	{
		void Notify(const FieaGameEngine::EventPublisher& eventPublisher) override;
		size_t Count{ 0 };
	};

	struct EventClearSubscriber final : FieaGameEngine::EventSubscriber
	{
		void Notify(const FieaGameEngine::EventPublisher& eventPublisher) override;
		size_t Count{ 0 };
	};
}

