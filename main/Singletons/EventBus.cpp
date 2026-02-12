#include "EventBus.h"

namespace gg
{
    EventBus::EventBus()
    {
        // Create event loop
        esp_event_loop_args_t eventLoopArgs{};
        eventLoopArgs.queue_size = 10;
        eventLoopArgs.task_name = "Event Loop"; // if not nullptr, a dedicated task will be assigned
        eventLoopArgs.task_priority = 5;
        eventLoopArgs.task_stack_size = 4096;
        eventLoopArgs.task_core_id = tskNO_AFFINITY;

        ESP_ERROR_CHECK(esp_event_loop_create(&eventLoopArgs, &m_EventLoopHandle));
    }

    EventBus::~EventBus()
    {
        // Clean up event loop
        ESP_ERROR_CHECK(esp_event_loop_delete(m_EventLoopHandle));
        m_EventLoopHandle = nullptr;
    }

    EventSubscription EventBus::Subscribe(esp_event_handler_t eventHandler, esp_event_base_t eventBase, int32_t eventId)
    {
        EventSubscription subscription{eventBase, eventId};
        ESP_ERROR_CHECK(esp_event_handler_instance_register_with(
            m_EventLoopHandle,
            eventBase,
            eventId,
            eventHandler,
            this,
            &subscription.instance)
        );

        return subscription;
    }
    
    void EventBus::Unsubscribe(const EventSubscription& subscription)
    {
        ESP_ERROR_CHECK(esp_event_handler_instance_unregister_with(
            m_EventLoopHandle,
            subscription.eventBase,
            subscription.eventId,
            subscription.instance)
        );
    }
}