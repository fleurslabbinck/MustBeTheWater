#include "Led.h"

#include "Singletons/LogManager.h"

namespace gg
{
    static constexpr uint32_t ON{1};
    static constexpr uint32_t OFF{0};

    const std::string Led::m_OnMessage{"LED ON"};
    const std::string Led::m_OffMessage{"LED OFF"};

    Led::Led(uint8_t gpioPin)
    : Component(gpioPin)
    {
        // Configure GPIO pin
        gpio_reset_pin(GetGpioId());
        gpio_set_direction(GetGpioId(), GPIO_MODE_OUTPUT);
    }

    void Led::TurnOn()
    {
        LogManager::Get().Log(GetGpioIdMessage(), m_OnMessage);
        gpio_set_level(GetGpioId(), ON);
    }

    void Led::TurnOff()
    {
        LogManager::Get().Log(GetGpioIdMessage(), m_OffMessage);
        gpio_set_level(GetGpioId(), OFF);
    }
}