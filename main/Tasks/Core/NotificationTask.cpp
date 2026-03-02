#include "NotificationTask.h"

namespace gg
{
    // Assign waittime in ms
    NotificationTask::NotificationTask(uint32_t waitTime)
        : m_WaitTicks{pdMS_TO_TICKS(waitTime)}
    {}

    void NotificationTask::Wait()
    {
        // Return if stop was requested while task execution
        if (StopRequested())
        {
            return;
        }

        // Task is blocked until it gets notified or the waiting time passes
        // No bits cleared on entry, all bits cleared on exit
        xTaskNotifyWait(0, 0xFFFFFFFF, &m_NotificationValue, m_WaitTicks);
    }

    // Reset delay time to max delay
    void NotificationTask::ResetWaitTime()
    {
        m_WaitTicks = portMAX_DELAY;
    }

    // Call to change time to delay task
    void NotificationTask::ChangeWaitTime(uint32_t waitTime)
    {
        m_WaitTicks = pdMS_TO_TICKS(waitTime);
    }

    void NotificationTask::Unblock()
    {
        const TaskHandle_t handle{GetHandle()};
        if (handle)
        {
            xTaskNotify(handle, 0, eNoAction);
        }
    }

    void NotificationTask::Unblock(uint32_t notificationValue)
    {
        const TaskHandle_t handle{GetHandle()};
        if (handle)
        {
            xTaskNotify(handle, notificationValue, eSetBits);
        }
    }
}