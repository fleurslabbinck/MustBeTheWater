#ifndef BLINKER_H
#define BLINKER_H

#include <string>
#include "driver/gpio.h"

namespace gg
{
    class Led final
    {
    public:
        Led(uint8_t gpioPin);
        ~Led() = default;
        Led(const Led&) = delete;
        Led(Led&&) = delete;
        Led& operator=(const Led&) = delete;
        Led& operator=(Led&&) = delete;

        void TurnOn();
        void TurnOff();

    private:
        bool m_On{false};
        const gpio_num_t m_GpioId{GPIO_NUM_NC};
        static const std::string m_OnMessage;
        static const std::string m_OffMessage;
        std::string m_GpioIdMessage{};
    };
}
#endif