#include "SoilSensor.h"

#include <algorithm>
#include "Singletons/LogManager.h"

namespace gg
{
    SoilSensor::SoilSensor(gpio_num_t gpio, adc_channel_t adcChannel, int dryReading, int wetReading, uint32_t startupDelay)
        : m_AdcChannel{adcChannel}, m_DryReading{dryReading}, m_WetReading{wetReading}, m_StartupDelay{pdMS_TO_TICKS(startupDelay)}, m_PowerSupply{gpio}
    {
        ConfigureAdc();
    }

    SoilSensor::~SoilSensor()
    {
        // Delete calibration handle
        ESP_ERROR_CHECK(adc_cali_delete_scheme_line_fitting(m_CalibrationHandle));
    }

    void SoilSensor::ConfigureAdc()
    {
        // Create ADC handle under oneshot mode
        adc_oneshot_unit_init_cfg_t handleConfig{};
        handleConfig.unit_id = ADC_UNIT_1; // ADC1 is better as ADC2 is also used by Wi-Fi
        handleConfig.ulp_mode = ADC_ULP_MODE_DISABLE; // Default

        ESP_ERROR_CHECK(adc_oneshot_new_unit(&handleConfig, &m_AdcHandle));

        // Configure ADC channel
        adc_oneshot_chan_cfg_t channelConfig{};
        channelConfig.atten = ADC_ATTEN_DB_12; // 150mV - 2450mV
        channelConfig.bitwidth = ADC_BITWIDTH_DEFAULT; // Driver will automatically select highest available resolution

        ESP_ERROR_CHECK(adc_oneshot_config_channel(m_AdcHandle, m_AdcChannel, &channelConfig));

        CalibrationSetup(handleConfig, channelConfig);
    }

    void SoilSensor::CalibrationSetup(const adc_oneshot_unit_init_cfg_t& handleConfig, const adc_oneshot_chan_cfg_t& channelConfig)
    {
        adc_cali_line_fitting_config_t calibrationConfig{};
        calibrationConfig.unit_id = handleConfig.unit_id;
        calibrationConfig.atten = channelConfig.atten;
        calibrationConfig.bitwidth = channelConfig.bitwidth;

        ESP_ERROR_CHECK(adc_cali_create_scheme_line_fitting(&calibrationConfig, &m_CalibrationHandle));
    }

    // Enables powers supply and delays to allow senser startup
    void SoilSensor::ApplyPower()
    {
        m_PowerSupply.Enable();
        vTaskDelay(m_StartupDelay);
    }

    // Stops supplying current the sensor
    void SoilSensor::RemovePower()
    {
        m_PowerSupply.Disable();
    }

    // Executes a sensor reading and returns a mapped result
    float SoilSensor::GetMoistureReading()
    {
        int rawAdc{};
        int adcValue{};

        ApplyPower();

        // Read raw result
        ESP_ERROR_CHECK(adc_oneshot_read(m_AdcHandle, m_AdcChannel, &rawAdc));
        LogManager::Get().Log("raw value: " + std::to_string(rawAdc) + "\n");

        RemovePower();

        // Calibrate the raw result;
        adc_cali_raw_to_voltage(m_CalibrationHandle, rawAdc, &adcValue);
        LogManager::Get().Log("calibrated value: " + std::to_string(adcValue) + "\n");

        // Return workable mapped value
        return MapValue(adcValue);
    }

    float SoilSensor::MapValue(int value)
    {
        float mappedValue{(static_cast<float>(value - m_DryReading)) / (m_WetReading - m_DryReading)};
        return std::clamp(mappedValue, 0.f, 1.f);
    }
}