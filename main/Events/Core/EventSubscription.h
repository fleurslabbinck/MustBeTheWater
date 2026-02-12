#ifndef EVENT_SUBSCRIPTION_H
#define EVENT_SUBSCRIPTION_H

#include "esp_event.h"

namespace gg
{
    using SubscriptionHandle = uint8_t;

    struct EventSubscription
    {
        explicit EventSubscription(esp_event_base_t eventBase, int32_t eventId)
            : eventId{eventId}, eventBase{eventBase}
        {
            AssignSubscriptionHandle();
        }
        
        SubscriptionHandle subscriptionHandle{};
        int32_t eventId{};
        esp_event_base_t eventBase{};
        esp_event_handler_instance_t instance{nullptr};

    private:
        inline static uint8_t totalSubscriptions{};

        // Assign unique subscription handle
        void AssignSubscriptionHandle()
        {
            subscriptionHandle = totalSubscriptions++;
        }
    };
}
#endif