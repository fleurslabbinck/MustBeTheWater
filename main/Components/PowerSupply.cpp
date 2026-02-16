#include "PowerSupply.h"

#include "esp_log.h"

static const char* TAG = "Powersupply";

namespace gg
{
    PowerSupply::PowerSupply(gpio_num_t gpio)
        : m_Gpio{gpio}
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
        ESP_LOGI(TAG, "GPIO %d: HIGH", m_Gpio);
        ESP_ERROR_CHECK(gpio_set_level(GetGpio(), 1));
    }

    void PowerSupply::Disable()
    {
        ESP_LOGI(TAG, "GPIO %d: LOW", m_Gpio);
        ESP_ERROR_CHECK(gpio_set_level(GetGpio(), 0));
    }
}