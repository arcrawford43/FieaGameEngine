#pragma once
#include "RTTI.h"
#include "Vector.h"
#include "EventSubscriber.h"
#include <memory>

namespace FieaGameEngine
{
    class EventPublisher :
        public RTTI
    {
        RTTI_DECLARATIONS(EventPublisher, RTTI)
    public:
        void Deliver() const;
        virtual ~EventPublisher() = default;
    protected:
        EventPublisher(const Vector<std::shared_ptr<EventSubscriber>>& listSubscribers);
        EventPublisher(const EventPublisher& other) = default;
        EventPublisher& operator=(const EventPublisher& other) = default;
        EventPublisher(EventPublisher&& other) = default;
        EventPublisher& operator=(EventPublisher&& other) = default;
    private:
        const Vector< std::shared_ptr<EventSubscriber>>* _listSubscribers;
    };
}

