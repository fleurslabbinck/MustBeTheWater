#include "SoilSensorTask.h"

#include "esp_log.h"
#include "Singletons/EventBus.h"
#include "Components/SoilSensor.h"

namespace gg
{
    static const char* TAG = "SoilSensor";

    SoilSensorTask::SoilSensorTask()
        : PeriodicNotificationTask(1000)
    {}

    void SoilSensorTask::Start()
    {
        // Task creation
        TaskConfig taskConfig{};
        taskConfig.name = "Soil Sensor Task";
        taskConfig.stackSize = 6144;
        taskConfig.priority = 10;
        CreateTask(taskConfig);

        // Soil sensor initialization
        SoilSensorConfig soilSensorConfig{};
        soilSensorConfig.gpio = GPIO_NUM_2;
        soilSensorConfig.adcChannel = ADC_CHANNEL_0;
        soilSensorConfig.dryRef = 2770;
        soilSensorConfig.wetRef = 430;
        soilSensorConfig.poweringDelay = 500;
        m_SoilSensor = std::make_unique<SoilSensor>(soilSensorConfig);
    }

    void SoilSensorTask::Execute()
    {
        m_Data = m_SoilSensor->GetMoistureReading();
        ESP_LOGI(TAG, "reading: %.2f", m_Data);

        EventBus::Get().PostEvent<float>(m_Data, MAIN_EVENTS, static_cast<int32_t>(MainEvents::ShareSensorData));
    }
}