#ifndef PERIODIC_NOTIFICATION_TASK_H
#define PERIODIC_NOTIFICATION_TASK_H

#include "Tasks/Core/NotificationTask.h"

namespace gg
{
    // Time accurate timed task
    class PeriodicNotificationTask : public NotificationTask
    {
    public:
        PeriodicNotificationTask() = default;
        PeriodicNotificationTask(uint32_t waitTime);
        PeriodicNotificationTask(const PeriodicNotificationTask&) = delete;
        PeriodicNotificationTask(PeriodicNotificationTask&&) = delete;
        PeriodicNotificationTask& operator=(const PeriodicNotificationTask&) = delete;
        PeriodicNotificationTask& operator=(PeriodicNotificationTask&&) = delete;

    protected:
        TickType_t m_LastWake{};

        void InitOnStart() override;
        void Wait() override;
        void Unblock() override;
    };
}
#endif