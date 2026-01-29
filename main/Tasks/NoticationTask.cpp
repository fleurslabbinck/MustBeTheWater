#include "NotificationTask.h"

namespace gg
{
    NotificationTask::NotificationTask(uint32_t waitTime)
    : m_WaitTicks{pdMS_TO_TICKS(waitTime)}
    {}

    bool NotificationTask::Wait()
    {
        // Task is blocked until it gets notified or the waiting time passes
        ulTaskNotifyTake(pdTRUE, m_WaitTicks);

        return !StopRequested();
    }

    void NotificationTask::Unblock()
    {
        const TaskHandle_t handle{GetHandle()};
        if (handle)
        {
            xTaskNotify(handle, 0, eNoAction);
        }
    }
}