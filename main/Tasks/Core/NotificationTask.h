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
        uint32_t m_NotificationValue{};
        TickType_t m_WaitTicks{portMAX_DELAY};

        bool IsBitSet(uint32_t bit) const {return m_NotificationValue & bit;}

        void Unblock() override;
        void Unblock(uint32_t notificationValue);
        void ChangeWaitTime(uint32_t waitTime);
        void ResetWaitTime();
        
    private:
        virtual void Wait() override;
    };
}
#endif