#ifndef BLINK_LED_TASK_H
#define BLINK_LED_TASK_H

#include "Tasks/Core/NotificationTask.h"
#include "Components/PowerSupply.h"

namespace gg
{
    class BlinkLedTask final : public NotificationTask
    {
        public:
        BlinkLedTask(gpio_num_t gpioPin, uint32_t waitTime);
        BlinkLedTask(const BlinkLedTask&) = delete;
        BlinkLedTask(BlinkLedTask&&) = delete;
        BlinkLedTask& operator=(const BlinkLedTask&) = delete;
        BlinkLedTask& operator=(BlinkLedTask&&) = delete;

        void Start();

    private:
        bool m_Blink{false};
        PowerSupply m_PowerSupply;

        void Execute() override;
    };
}
#endif