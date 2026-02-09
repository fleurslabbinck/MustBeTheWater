#ifndef BLINK_LED_TASK_H
#define BLINK_LED_TASK_H

#include <memory>
#include <driver/gpio.h>

#include "Tasks/Core/NotificationTask.h"

namespace gg
{
    class PowerSupply;
    class BlinkLedTask final : public NotificationTask
    {
        public:
        BlinkLedTask(uint32_t waitTime);
        BlinkLedTask(const BlinkLedTask&) = delete;
        BlinkLedTask(BlinkLedTask&&) = delete;
        BlinkLedTask& operator=(const BlinkLedTask&) = delete;
        BlinkLedTask& operator=(BlinkLedTask&&) = delete;

        void Start(const TaskAssembly& taskAssembly, gpio_num_t gpioPin);

    private:
        bool m_Blink{false};
        std::unique_ptr<PowerSupply> m_PowerSupply{nullptr};

        void Execute() override;
    };
}
#endif