#include "SoilSensorTask.h"

#include "esp_log.h"
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

        // Event loop creation
        TaskConfig eventLoopConfig{};
        eventLoopConfig.name = "Soil Sensor Event Loop";
        eventLoopConfig.stackSize = 3084;
        eventLoopConfig.priority = 5;
        CreateEventLoop(eventLoopConfig, 5);

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
        float reading{m_SoilSensor->GetMoistureReading()};
        ESP_LOGI(TAG, "reading: %.2f", reading);
    }
}