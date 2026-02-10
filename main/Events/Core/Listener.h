#ifndef LISTENER_H
#define LISTENER_H

#include <vector>
#include "Events/Core/Sender.h"
#include "Events/Core/EventSubscription.h"

namespace gg
{
    class Listener
    {
    public:
        Listener();
        virtual ~Listener();
        Listener(const Listener&) = delete;
        Listener(Listener&&) = delete;
        Listener& operator=(const Listener&) = delete;
        Listener& operator=(Listener&&) = delete;

        SubscriptionHandle SubscribeToEvent(const Sender& sender, esp_event_handler_t eventHandler, esp_event_base_t eventBase, int32_t eventId);

        void UnsubscribeFromEvent(SubscriptionHandle subscriptionHandle);

    private:
        const size_t m_MaxSubscriptions{5};
        std::vector<EventSubscription> m_EventSubscriptions{};

        void Unsubscribe(const EventSubscription& subscription) const;
    };
}
#endif