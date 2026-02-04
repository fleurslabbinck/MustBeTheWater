#include "SoilSensorTask.h"

#include "esp_log.h"
#include "Components/SoilSensor.h"

namespace gg
{
    static const char* TAG = "SoilSensor";

    SoilSensorTask::SoilSensorTask(gpio_num_t gpio, adc_channel_t adcChannel, int dryReading, int wetReading, uint32_t startupDelay, uint32_t waitTime)
        : PeriodicNotificationTask(waitTime), m_SoilSensor{gpio, adcChannel, dryReading, wetReading, startupDelay}
    {}

    void SoilSensorTask::Start()
    {
        Init("Soil Sensor Task", 6144, 10);
    }

    void SoilSensorTask::Execute()
    {
        float reading{m_SoilSensor.GetMoistureReading()};
        ESP_LOGI(TAG, "reading: %.2f", reading);
    }
}