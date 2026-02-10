#include "Listener.h"

#include <algorithm>

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
            Unsubscribe(subscription);
        }
    }
    
    // Subscribe event handler to event
    // CALL AFTER EVENT LOOP CREATION!
    // esp_event_handler_t should be static function with args: void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData
    SubscriptionHandle Listener::SubscribeToEvent(const Sender& sender, esp_event_handler_t eventHandler, esp_event_base_t eventBase, int32_t eventId)
    {
        esp_event_loop_handle_t eventLoopHandle{sender.GetEventLoopHandle()};

        EventSubscription subscription{eventLoopHandle, eventBase, eventId};
        ESP_ERROR_CHECK(esp_event_handler_instance_register_with(
            eventLoopHandle,
            eventBase,
            eventId,
            eventHandler,
            this,
            &subscription.instance
        ));

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
            Unsubscribe(m_EventSubscriptions[idx]);

            m_EventSubscriptions.erase(it);
        }
    }

    void Listener::Unsubscribe(const EventSubscription& subscription) const
    {
        ESP_ERROR_CHECK(esp_event_handler_instance_unregister_with(
            subscription.eventLoopHandle,
            subscription.eventBase,
            subscription.eventId,
            subscription.instance
        ));
    }
}