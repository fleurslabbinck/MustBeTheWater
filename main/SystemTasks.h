#ifndef SYSTEM_TASKS_H
#define SYSTEM_TASKS_H

#include "Tasks/BlinkLedTask.h"

namespace gg
{
    constexpr uint8_t BLINK_GPIO_A{2};
    constexpr uint32_t WAIT_TIME_A{1000};
    constexpr uint8_t BLINK_GPIO_B{4};
    constexpr uint32_t WAIT_TIME_B{700};

    // Register all tasks
    struct SystemTasks
    {
        inline static BlinkLedTask s_BlinkLedTaskA{BLINK_GPIO_A, WAIT_TIME_A};
        inline static BlinkLedTask s_BlinkLedTaskB{BLINK_GPIO_B, WAIT_TIME_B};
    };
}
#endif