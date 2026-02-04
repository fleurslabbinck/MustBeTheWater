#include "PowerSupply.h"

#include "Singletons/LogManager.h"

namespace gg
{
    PowerSupply::PowerSupply(gpio_num_t gpio)
        : m_Gpio{gpio}, m_GpioId{"(GPIO " + std::to_string(m_Gpio) + ")"}
    {
        ConfigureGpio();
    }

    void PowerSupply::ConfigureGpio()
    {
        ESP_ERROR_CHECK(gpio_reset_pin(m_Gpio));
        ESP_ERROR_CHECK(gpio_set_direction(m_Gpio, GPIO_MODE_OUTPUT));
    }

    void PowerSupply::Enable()
    {
        LogManager::Get().Log(GetGpioId(), "GPIO HIGH");
        ESP_ERROR_CHECK(gpio_set_level(GetGpio(), 1));
    }

    void PowerSupply::Disable()
    {
        LogManager::Get().Log(GetGpioId(), "GPIO LOW");
        ESP_ERROR_CHECK(gpio_set_level(GetGpio(), 0));
    }
}