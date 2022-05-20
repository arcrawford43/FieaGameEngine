#pragma once
#include "Vector.h"
#include "EventPublisher.h"
#include "GameTime.h"

using namespace std::chrono_literals;
namespace FieaGameEngine
{
	struct Queue final
	{
		Queue(std::shared_ptr<EventPublisher> eventPublisher , const std::chrono::high_resolution_clock::time_point& time, std::chrono::milliseconds delay = 0ms)
			:Event(eventPublisher), TimeExpired(time + delay)
		{};
		std::shared_ptr<EventPublisher> Event;
		std::chrono::high_resolution_clock::time_point TimeExpired;
	};

	class EventQueue final
	{
	public:
		void Enqueue(std::shared_ptr<EventPublisher> eventPublisher, const GameTime& gametime, std::chrono::milliseconds delay = 0ms);
		void Update(const GameTime& gameTime);
		void Clear();
		std::size_t Size() const;
		bool IsEmpty() const;

	private:
		bool _isUpdating;
		bool _pendingClear;
		Vector<Queue> _queue{ 10 };
		Vector<Queue> _pending{ 10 };
	};
}
