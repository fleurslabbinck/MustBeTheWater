#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "driver/gpio.h"

namespace gg
{
    class Component
    {
    public:
        Component(uint8_t gpioPin) :
            m_GpioId{static_cast<gpio_num_t>(gpioPin)},
            m_GpioIdMessage{"(GPIO " + std::to_string(m_GpioId) + ")"}
        {}

        ~Component() = default;
        Component(const Component&) = delete;
        Component(Component&&) = delete;
        Component& operator=(const Component&) = delete;
        Component& operator=(Component&&) = delete;

        gpio_num_t GetGpioId() const {return m_GpioId;}
        const std::string& GetGpioIdMessage() const {return m_GpioIdMessage;}

    private:
        const gpio_num_t m_GpioId{GPIO_NUM_NC};
        std::string m_GpioIdMessage{};
    };
}
#endif