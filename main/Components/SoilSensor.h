#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"

#include "Components/PowerSupply.h"

namespace gg
{
    struct SoilSensorConfig
    {
        gpio_num_t gpio{GPIO_NUM_2};
        adc_channel_t adcChannel{ADC_CHANNEL_0};
        int dryRef{};
        int wetRef{};
        uint32_t poweringDelay{500};
    };
    
    class SoilSensor final
    {        
    public:
        explicit SoilSensor(const SoilSensorConfig& assembly);
        ~SoilSensor();
        SoilSensor(const SoilSensor&) = delete;
        SoilSensor(SoilSensor&&) = delete;
        SoilSensor& operator=(const SoilSensor&) = delete;
        SoilSensor& operator=(SoilSensor&&) = delete;

        void ApplyPower();
        void RemovePower();

        TickType_t GetPoweringDelay() const {return m_PoweringDelay;}
        float GetSample();

    private:
        const adc_channel_t m_AdcChannel{};
        const int m_DryRef{};
        const int m_WetRef{};
        const TickType_t m_PoweringDelay{};
        PowerSupply m_PowerSupply;
        adc_oneshot_unit_handle_t m_AdcHandle{nullptr};
        adc_cali_handle_t m_CalibrationHandle{nullptr};

        void ConfigureAdc();
        void CalibrationSetup(const adc_oneshot_unit_init_cfg_t& handleConfig, const adc_oneshot_chan_cfg_t& channelConfig);

        float MapValue(int value);
    };
}
#endif