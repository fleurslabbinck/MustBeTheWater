#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"

#include "Components/PowerSupply.h"

namespace gg
{
    class SoilSensor final
    {
    public:
        explicit SoilSensor(gpio_num_t gpio, adc_channel_t adcChannel, int dryReading, int wetReading, uint32_t startupDelay);
        ~SoilSensor();
        SoilSensor(const SoilSensor&) = delete;
        SoilSensor(SoilSensor&&) = delete;
        SoilSensor& operator=(const SoilSensor&) = delete;
        SoilSensor& operator=(SoilSensor&&) = delete;

        float GetMoistureReading();

    private:
        const adc_channel_t m_AdcChannel{};
        const int m_DryReading{};
        const int m_WetReading{};
        const TickType_t m_StartupDelay{};
        PowerSupply m_PowerSupply;
        adc_oneshot_unit_handle_t m_AdcHandle{nullptr};
        adc_cali_handle_t m_CalibrationHandle{nullptr};

        void ConfigureAdc();
        void CalibrationSetup(const adc_oneshot_unit_init_cfg_t& handleConfig, const adc_oneshot_chan_cfg_t& channelConfig);

        void ApplyPower();
        void RemovePower();

        float MapValue(int value);
    };
}
#endif