#ifndef NOTIFICATION_TASK_H
#define NOTIFICATION_TASK_H

#include "Tasks/Core/Task.h"

namespace gg
{
    // Simple timed task, not completely time accurate
    class NotificationTask : public Task
    {
    public:
        NotificationTask() = default;
        NotificationTask(uint32_t waitTime);
        NotificationTask(const NotificationTask&) = delete;
        NotificationTask(NotificationTask&&) = delete;
        NotificationTask& operator=(const NotificationTask&) = delete;
        NotificationTask& operator=(NotificationTask&&) = delete;

    protected:
        void Unblock() override;
        
    private:
        TickType_t m_WaitTicks{portMAX_DELAY};

        bool WaitForWork() override;
    };
}
#endif