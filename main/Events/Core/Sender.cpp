#include "Sender.h"

namespace gg
{
    void Sender::CreateEventLoop(const TaskAssembly& taskAssembly, int32_t queueSize)
    {
        // Create event loop
        esp_event_loop_args_t eventLoopArgs{};
        eventLoopArgs.queue_size = queueSize;
        eventLoopArgs.task_name = taskAssembly.name; // if not nullptr, a dedicated task will be assigned
        eventLoopArgs.task_priority = taskAssembly.priority;
        eventLoopArgs.task_stack_size = taskAssembly.stackSize;
        eventLoopArgs.task_core_id = taskAssembly.GetCoreId();

        ESP_ERROR_CHECK(esp_event_loop_create(&eventLoopArgs, &m_EventLoopHandle));
    }

    Sender::~Sender()
    {
        ESP_ERROR_CHECK(esp_event_loop_delete(m_EventLoopHandle));
        m_EventLoopHandle = nullptr;
    }
}