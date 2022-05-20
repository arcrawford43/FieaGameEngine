#pragma once
#include "EventPublisher.h"
#include <memory>

namespace FieaGameEngine
{
	enum class ChangeSubscriberTypes
	{
		Subscribe,
		Unsubscribe,
		UnsubscribeAll
	};
	struct ChangeSubscriber final
	{
		ChangeSubscriberTypes Type;
		std::shared_ptr<EventSubscriber> Subscriber;
	};

	template <typename T>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event<T>, EventPublisher)
	public:
		Event(const T& message);
		Event(T&& message);
		Event(const Event& other) = default;
		Event& operator=(const Event& other) = default;
		Event(Event&& other) = default;
		Event& operator=(Event&& other) = default;

		const T& Message() const;
		
		static void Subscribe(std::shared_ptr<EventSubscriber> subscriber);
		static void Unsubscribe(std::shared_ptr<EventSubscriber> subcriber);
		static void UnsubscribeAll();
		static void HandleChangeList();

	private:
		inline static Vector<std::shared_ptr<EventSubscriber>> sListSubscribers{ 10 };
		inline static Vector<ChangeSubscriber> sChangeList{ 10 };;
		T _message;
	};

}

#include "Event.inl"