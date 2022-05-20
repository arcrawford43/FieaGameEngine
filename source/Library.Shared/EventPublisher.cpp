#include "pch.h"
#include "EventPublisher.h"

using namespace std;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventPublisher)
	EventPublisher::EventPublisher(const Vector<shared_ptr<EventSubscriber>>& listSubscribers)
		: _listSubscribers(&listSubscribers)
	{
	}

	void EventPublisher::Deliver() const
	{
		for (size_t i = 0; i < _listSubscribers->Size(); ++i)
		{
			_listSubscribers->At(i)->Notify(*this);
		}
	}
}