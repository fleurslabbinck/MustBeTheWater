#ifndef POWER_SUPPLY_H
#define POWER_SUPPLY_H

#include <string>
#include "driver/gpio.h"

namespace gg
{
    class PowerSupply final
    {
    public:
        PowerSupply(gpio_num_t gpio);
        ~PowerSupply() = default;
        PowerSupply(const PowerSupply&) = delete;
        PowerSupply(PowerSupply&&) = delete;
        PowerSupply& operator=(const PowerSupply&) = delete;
        PowerSupply& operator=(PowerSupply&&) = delete;

        gpio_num_t GetGpio() const {return m_Gpio;}
        const std::string& GetGpioId() const {return m_GpioId;}

        void Enable();
        void Disable();

    private:
        const gpio_num_t m_Gpio{GPIO_NUM_NC};
        std::string m_GpioId{};
        
        virtual void ConfigureGpio();
    };
}
#endif