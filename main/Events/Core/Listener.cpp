#include "Listener.h"

#include <algorithm>
#include "Singletons/EventBus.h"

namespace gg
{
    Listener::Listener()
    {
        m_EventSubscriptions.reserve(m_MaxSubscriptions);
    }

    Listener::~Listener()
    {
        for (const EventSubscription& subscription : m_EventSubscriptions)
        {
            EventBus::Get().Unsubscribe(subscription);
        }
    }
    
    // Subscribe event handler to event
    // esp_event_handler_t should be static function with args: void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData
    SubscriptionHandle Listener::SubscribeToEvent(esp_event_handler_t eventHandler, esp_event_base_t eventBase, int32_t eventId)
    {
        EventSubscription subscription{EventBus::Get().Subscribe(eventHandler, eventBase, eventId)};
        m_EventSubscriptions.push_back(subscription);
        return m_EventSubscriptions.back().subscriptionHandle;
    }

    // Unsubscribe event handler from event
    void Listener::UnsubscribeFromEvent(SubscriptionHandle subscriptionHandle)
    {
        // Find iterator to subscribtion in vector and erase
        auto it{std::find_if(
            m_EventSubscriptions.begin(),
            m_EventSubscriptions.end(),
            [&](const EventSubscription& subscription)
            {
                return subscriptionHandle == subscription.subscriptionHandle;
            }
        )};

        if (it != m_EventSubscriptions.end())
        {
            // Get index from iterator
            int idx{std::distance(m_EventSubscriptions.begin(), it)};

            // Unregister instance from event loop
            EventBus::Get().Unsubscribe(m_EventSubscriptions[idx]);

            m_EventSubscriptions.erase(it);
        }
    }
}