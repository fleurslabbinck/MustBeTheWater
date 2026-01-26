#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "Components/Led.h"

// (GPIO 2 is responsible for onboard LED)
constexpr uint8_t BLINK_GPIO{2};

extern "C" void app_main(void)
{
    using namespace gg;

    Led Blinker{BLINK_GPIO};

    // Blink loop
    while (true)
    {
        Blinker.TurnOn();
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second

        Blinker.TurnOff();
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second
    }
}
