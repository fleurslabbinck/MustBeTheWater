#include "Task.h"

#include "Singletons/LogManager.h"

namespace gg
{
    // Call to create and start task pinned to specific core
    void Task::Init(const std::string& name, uint32_t stackSize, uint8_t priority, CoreSelect core)
    {
        BaseType_t coreIdx{static_cast<BaseType_t>(core)};
        if (core == CoreSelect::None)
        {
            coreIdx = tskNO_AFFINITY;
        }

        int createIdx{xTaskCreatePinnedToCore(
            TaskEntry, 
            name.c_str(), 
            stackSize, 
            this, 
            static_cast<UBaseType_t>(priority), 
            &m_Handle, 
            coreIdx)
        };

        if (createIdx > 0)
        {
            LogManager::Get().Log("TASK (" + name + ") CREATED SUCCESSFULLY\n");
        }
        else
        {
            LogManager::Get().Log("TASK (" + name + ") FAILED: COULD NOT ALLOCATE MEMORY\n");
        }
    }

    // Call to create and start task
    void Task::Init(const std::string& name, uint32_t stackSize, uint8_t priority)
    {
        Init(name, stackSize, priority, CoreSelect::None);
    }

    // C-style function that starts the task
    void Task::TaskEntry(void* pvParameters)
    {
        Task* self{static_cast<Task*>(pvParameters)};
        self->Run();
    }

    // Task loop
    void Task::Run()
    {
        while (!StopRequested())
        {
            // Wait and check if task is ready to execute
            if (Wait())
            {
                Execute();
            }
        }

        // Avoid dangling pointer
        m_Handle = nullptr;

        // Clean up when task has ended
        vTaskDelete(nullptr);
    }

    // Don't suspend task that is holding a mutex, can cause system to deadlock
    void Task::Suspend()
    {
        if (m_Handle)
        {
            vTaskSuspend(m_Handle);
        }
    }

    // Resume suspended task
    void Task::Resume()
    {
        if (m_Handle)
        {
            vTaskResume(m_Handle);
        }
    }

    // Request to end the ongoing task
    void Task::End()
    {
        m_StopRequested.store(true, std::memory_order_relaxed);

        // Unblock task so request can get consumed
        Unblock();
    }
}