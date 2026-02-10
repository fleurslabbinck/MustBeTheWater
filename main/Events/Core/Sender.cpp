#include "Sender.h"

namespace gg
{
    void Sender::PinEventLoopToCore(CoreSelect core)
    {
        m_Core = TaskConfig::GetCoreId(core);
    }

    void Sender::CreateEventLoop(const TaskConfig& taskConfig, int32_t queueSize)
    {
        // Create event loop
        esp_event_loop_args_t eventLoopArgs{};
        eventLoopArgs.queue_size = queueSize;
        eventLoopArgs.task_name = taskConfig.name; // if not nullptr, a dedicated task will be assigned
        eventLoopArgs.task_priority = taskConfig.priority;
        eventLoopArgs.task_stack_size = taskConfig.stackSize;
        eventLoopArgs.task_core_id = m_Core;

        ESP_ERROR_CHECK(esp_event_loop_create(&eventLoopArgs, &m_EventLoopHandle));
    }

    Sender::~Sender()
    {
        ESP_ERROR_CHECK(esp_event_loop_delete(m_EventLoopHandle));
        m_EventLoopHandle = nullptr;
    }
}