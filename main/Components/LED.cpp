#include "LED.h"

#include <string>

#include "Singletons/LogManager.h"

namespace gg
{
    constexpr uint32_t OFF{0};
    constexpr uint32_t ON{1};

    LED::LED(uint8_t gpioPin)
    : m_GpioPin{static_cast<gpio_num_t>(gpioPin)}
    {
        // Configure GPIO pin
        gpio_reset_pin(m_GpioPin);
        gpio_set_direction(m_GpioPin, GPIO_MODE_OUTPUT);
    }

    void LED::TurnOn()
    {
        LogManager::Get().Log("LED" + std::to_string(m_GpioPin) + "ON\n");
        gpio_set_level(m_GpioPin, ON);
    }

    void LED::TurnOff()
    {
        LogManager::Get().Log("LED" + std::to_string(m_GpioPin) + "OFF\n");
        gpio_set_level(m_GpioPin, OFF);
    }
}