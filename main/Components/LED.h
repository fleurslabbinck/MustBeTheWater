#ifndef BLINKER_H
#define BLINKER_H

#include "driver/gpio.h"

namespace gg
{
    class LED final
    {
    public:
        LED(uint8_t gpioPin);
        ~LED() = default;
        LED(const LED& other) = delete;
        LED(LED&& other) = delete;
        LED& operator=(const LED& other) = delete;
        LED& operator=(LED&& other) = delete;

        void TurnOn();
        void TurnOff();

    private:
        bool m_On{false};
        const gpio_num_t m_GpioPin{GPIO_NUM_NC};
    };
}
#endif