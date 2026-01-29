#include "Led.h"

#include "Singletons/LogManager.h"

namespace gg
{
    static constexpr uint32_t ON{1};
    static constexpr uint32_t OFF{0};

    const std::string Led::m_OnMessage{"LED ON"};
    const std::string Led::m_OffMessage{"LED OFF"};

    Led::Led(uint8_t gpioPin)
    : m_GpioId{static_cast<gpio_num_t>(gpioPin)}
    {
        // Assemble pin ID
        m_GpioIdMessage = "(GPIO " + std::to_string(m_GpioId) + ")";

        // Configure GPIO pin
        gpio_reset_pin(m_GpioId);
        gpio_set_direction(m_GpioId, GPIO_MODE_OUTPUT);
    }

    void Led::TurnOn()
    {
        LogManager::Get().Log(m_GpioIdMessage, m_OnMessage);
        gpio_set_level(m_GpioId, ON);
    }

    void Led::TurnOff()
    {
        LogManager::Get().Log(m_GpioIdMessage, m_OffMessage);
        gpio_set_level(m_GpioId, OFF);
    }
}