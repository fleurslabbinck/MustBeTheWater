#include "PeriodicNotificationTask.h"

namespace gg
{
    // Assign waitTime in ms
    PeriodicNotificationTask::PeriodicNotificationTask(uint32_t waitTime)
        : m_WaitTicks{pdMS_TO_TICKS(waitTime)}
    {}

    // Init last wake on task start
    void PeriodicNotificationTask::InitOnStart()
    {
        m_LastWake = xTaskGetTickCount();
    }

    void PeriodicNotificationTask::Wait()
    {
        // Return if stop was requested while task execution
        if (StopRequested())
        {
            return;
        }

        // Get current and calculate elapsed time
        const TickType_t now{xTaskGetTickCount()};
        const TickType_t elapsed{now - m_LastWake};
        
        if (elapsed < m_WaitTicks)
        {
            // Task is blocked until it gets notified or the adjusted waiting time passes
            ulTaskNotifyTake(pdTRUE, m_WaitTicks - elapsed);
        }

        // Update wake time
        m_LastWake = xTaskGetTickCount();
    }

    void PeriodicNotificationTask::Unblock()
    {
        const TaskHandle_t handle{GetHandle()};
        if (handle)
        {
            xTaskNotify(handle, 0, eNoAction);
        }
    }
}