#include "Event.h"

namespace FieaGameEngine
{
	template <typename T>
	RTTI_DEFINITIONS(Event<T>)

	template <typename T>
	Event<T>::Event(const T& message)
		:_message(message), EventPublisher(sListSubscribers)
	{
	}

	template <typename T>
	Event<T>::Event(T&& message)
		: _message(std::move(message)), EventPublisher(sListSubscribers)
	{
	}

	template<typename T>
	inline const T& Event<T>::Message() const
	{
		return _message;
	}

	template<typename T>
	inline void Event<T>::Subscribe(std::shared_ptr<EventSubscriber> subscriber)
	{
		sChangeList.PushBack({ ChangeSubscriberTypes::Subscribe, std::move(subscriber) });
	}

	template<typename T>
	inline void Event<T>::Unsubscribe(std::shared_ptr<EventSubscriber> subscriber)
	{
		sChangeList.PushBack({ ChangeSubscriberTypes::Unsubscribe, std::move(subscriber) });
	}

	template<typename T>
	inline void Event<T>::UnsubscribeAll()
	{
		sChangeList.Clear();
		sChangeList.PushBack({ ChangeSubscriberTypes::UnsubscribeAll, nullptr });
	}

	template <typename T>
	void Event<T>::HandleChangeList()
	{
		for (size_t i = 0; i < sChangeList.Size(); ++i)
		{
			ChangeSubscriber changeSubscriber = sChangeList[i];
			switch (changeSubscriber.Type)
			{
				case ChangeSubscriberTypes::Subscribe :
					if (sListSubscribers.end() == sListSubscribers.Find(changeSubscriber.Subscriber))
					{
						sListSubscribers.PushBack(changeSubscriber.Subscriber);
					}
					break;

				case ChangeSubscriberTypes::Unsubscribe :
					sListSubscribers.Remove(changeSubscriber.Subscriber);
					break;

				case ChangeSubscriberTypes::UnsubscribeAll :
					sListSubscribers.Clear();
			}
		}

		sChangeList.Clear();
	}
}