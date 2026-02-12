#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include "esp_event.h"
#include "Singletons/Singleton.h"
#include "Events/Core/EventSubscription.h"

namespace gg
{
    class EventBus : public Singleton<EventBus>
    {
        friend class Listener;
    public:
        ~EventBus() override;
        EventBus(const EventBus&) = delete;
        EventBus(EventBus&&) = delete;
        EventBus& operator=(const EventBus&) = delete;
        EventBus& operator=(EventBus&&) = delete;

        // Ensure data will still exist when accessed be listener
        template<typename DataType>
        void PostEvent(const DataType& eventData, esp_event_base_t eventBase, int32_t eventId)
        {
            ESP_ERROR_CHECK(esp_event_post_to(
                m_EventLoopHandle,
                eventBase,
                eventId,
                &eventData,
                sizeof(eventData),
                portMAX_DELAY
            ));
        }
    
    private:
        friend class Singleton<EventBus>;
        EventBus();

        esp_event_loop_handle_t m_EventLoopHandle{nullptr};

        EventSubscription Subscribe(esp_event_handler_t eventHandler, esp_event_base_t eventBase, int32_t eventId);
        void Unsubscribe(const EventSubscription& subscription);
};
}
#endif