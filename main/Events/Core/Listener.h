#ifndef LISTENER_H
#define LISTENER_H

#include <vector>
#include "Singletons/EventBus.h"

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

    protected:
        SubscriptionHandle SubscribeToEvent(void* object, esp_event_handler_t eventHandler, esp_event_base_t eventBase, int32_t eventId);
        void UnsubscribeFromEvent(SubscriptionHandle subscriptionHandle);

    private:
        const size_t m_MaxSubscriptions{5};
        std::vector<EventSubscription> m_EventSubscriptions{};
    };
}
#endif