#ifndef SYSTEM_TASKS_H
#define SYSTEM_TASKS_H

#include "Tasks/SoilSensorTask.h"
#include "Tasks/BlinkLedTask.h"

namespace gg
{
    constexpr gpio_num_t SENSOR_GPIO{GPIO_NUM_4};
    constexpr adc_channel_t ADC_CHANNEL{ADC_CHANNEL_0};
    constexpr int DRY_VALUE{2770};
    constexpr int WET_VALUE{430};
    constexpr uint32_t STARTUP_DELAY{500};

    constexpr gpio_num_t BLINK_GPIO{GPIO_NUM_2};
    constexpr uint32_t WAIT_TIME{1000};

    // Register all tasks
    struct SystemTasks
    {
        inline static SoilSensorTask s_SoilSensorTask{SENSOR_GPIO, ADC_CHANNEL, DRY_VALUE, WET_VALUE, STARTUP_DELAY, WAIT_TIME};
        inline static BlinkLedTask s_BlinkLedTask{BLINK_GPIO, WAIT_TIME};
    };
}
#endif