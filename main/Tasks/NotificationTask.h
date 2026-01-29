#ifndef NOTIFICATION_TASK_H
#define NOTIFICATION_TASK_H

#include "Task.h"

namespace gg
{
    class NotificationTask : public Task
    {
    public:
        NotificationTask(uint32_t waitTime);
        NotificationTask(const NotificationTask&) = delete;
        NotificationTask(NotificationTask&&) = delete;
        NotificationTask& operator=(const NotificationTask&) = delete;
        NotificationTask& operator=(NotificationTask&&) = delete;

    protected:
        TickType_t m_WaitTicks{portMAX_DELAY};

        bool WaitForWork() override;
        void Unblock() override;
    };
}
#endif