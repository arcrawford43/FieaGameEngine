#include "pch.h"
#include "EventQueue.h"
#include <algorithm>

namespace FieaGameEngine
{
	void EventQueue::Enqueue(std::shared_ptr<EventPublisher> eventPublisher, const GameTime& gametime, std::chrono::milliseconds delay)
	{
		if (_isUpdating)
		{
			_pending.PushBack({ std::move(eventPublisher), gametime.CurrentTime(), delay });
		}
		else
		{
			_queue.PushBack({ std::move(eventPublisher), gametime.CurrentTime(), delay });
		}
	}

	void EventQueue::Clear()
	{
		if (_isUpdating)
		{
			_pending.Clear();
			_pendingClear = true;
		}
		else
		{
			_queue.Clear();
		}
	}

	std::size_t EventQueue::Size() const
	{
		return _queue.Size() + _pending.Size();
	}

	bool EventQueue::IsEmpty() const
	{
		return (_queue.IsEmpty() && _pending.IsEmpty());
	}

	void EventQueue::Update(const GameTime& gameTime)
	{
		_isUpdating = true;
		auto iteratorEnd = _queue.end();
		auto iterator = std::partition(_queue.begin(), iteratorEnd,
			[&gameTime](Queue queue) {return gameTime.CurrentTime() <= queue.TimeExpired; });

		for (auto iteratorCopy = iterator; iteratorCopy != iteratorEnd; ++iteratorCopy)
		{
			(*iteratorCopy).Event->Deliver();
		}

		if (iterator != iteratorEnd)
		{
			_queue.Remove(iterator, iteratorEnd);
		}
		_isUpdating = false;

		if (_pendingClear)
		{
			_queue.Clear();
		}
		for (size_t i = 0; i < _pending.Size(); ++i)
		{
			_queue.PushBack(std::move(_pending[i]));
		}
		_pending.Clear();
	}
}