#ifndef PERIODIC_NOTIFICATION_TASK_H
#define PERIODIC_NOTIFICATION_TASK_H

#include "Tasks/Core/Task.h"

namespace gg
{
    // Time accurate timed task
    class PeriodicNotificationTask : public Task
    {
    public:
        PeriodicNotificationTask(uint32_t waitTime);
        PeriodicNotificationTask(const PeriodicNotificationTask&) = delete;
        PeriodicNotificationTask(PeriodicNotificationTask&&) = delete;
        PeriodicNotificationTask& operator=(const PeriodicNotificationTask&) = delete;
        PeriodicNotificationTask& operator=(PeriodicNotificationTask&&) = delete;

    protected:
        const TickType_t m_WaitTicks;
        TickType_t m_LastWake{};

        void InitOnStart() override;
        bool WaitForWork() override;
        void Unblock() override;
    };
}
#endif