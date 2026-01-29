#ifndef BLINK_LED_TASK_H
#define BLINK_LED_TASK_H

#include "Tasks/NotificationTask.h"
#include "Components/Led.h"

namespace gg
{
    class BlinkLedTask final : public NotificationTask
    {
        public:
        BlinkLedTask(uint8_t gpioPin, uint32_t waitTime);
        BlinkLedTask(const BlinkLedTask&) = delete;
        BlinkLedTask(BlinkLedTask&&) = delete;
        BlinkLedTask& operator=(const BlinkLedTask&) = delete;
        BlinkLedTask& operator=(BlinkLedTask&&) = delete;

        void Start();

    private:
        bool m_Blink{false};
        Led m_Led;

        void Execute() override;
    };
}
#endif