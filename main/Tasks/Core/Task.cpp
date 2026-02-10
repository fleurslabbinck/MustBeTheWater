#include "Task.h"

#include "Singletons/LogManager.h"

namespace gg
{
    Task::~Task()
    {
        m_Handle = nullptr;
    }

    // Call to pin task to one core
    // Pinned to no core by default
    void Task::PinTaskToCore(CoreSelect core)
    {
        m_Core = TaskConfig::GetCoreId(core);
    }

    // Call to create and start task pinned to specific core
    void Task::CreateTask(const TaskConfig& taskConfig)
    {
        int createIdx{xTaskCreatePinnedToCore(
            TaskEntry, 
            taskConfig.name, 
            taskConfig.stackSize, 
            this, 
            taskConfig.priority, 
            &m_Handle, 
            m_Core)
        };

        if (createIdx > 0)
        {
            LogManager::Get().Log(std::string(taskConfig.name), "TASK CREATED SUCCESSFULLY");
        }
        else
        {
            LogManager::Get().Log(std::string(taskConfig.name), "FAILED: COULD NOT ALLOCATE MEMORY");
        }
    }
    
    // C-style function that starts the task
    void Task::TaskEntry(void* args)
    {
        Task* self{static_cast<Task*>(args)};
        self->Run();
    }

    // Task loop
    void Task::Run()
    {
        InitOnStart();

        while (!StopRequested())
        {
            // Wait and check if task is ready to execute
            if (WaitForWork())
            {
                Execute();
            }
        }

        // Clean up when task has ended
        vTaskDelete(nullptr);
    }

    // Cause task to be suspended and never get any CPU time no matter the priority
    // Don't suspend task that is holding a mutex, can cause system to deadlock!
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

        // Revoke external control
        m_Handle = nullptr;
    }
}