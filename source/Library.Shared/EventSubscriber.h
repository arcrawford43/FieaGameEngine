#pragma once

namespace FieaGameEngine
{
	class EventPublisher;
	class EventSubscriber
	{
	public:
		virtual void Notify(const EventPublisher& eventPublisher) = 0;
		virtual ~EventSubscriber() = default;
	};
}