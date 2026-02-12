#include "SoilSensorTask.h"

#include "esp_log.h"
#include "Events/Events.h"

namespace gg
{
    static const char* TAG = "SoilSensor";

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

        // Subscribe to events
        SubscribeToEvent(OnSoilSensorDataRequested, MAIN_EVENTS, static_cast<int32_t>(MainEvents::RequestSensorData));
    }

    void SoilSensorTask::Execute()
    {
        m_Data = m_SoilSensor->GetMoistureReading();
        ESP_LOGI(TAG, "reading: %.2f", m_Data);

        EventBus::Get().PostEvent<float>(m_Data, MAIN_EVENTS, static_cast<int32_t>(MainEvents::ShareSensorData));
    }

    void SoilSensorTask::WakeForReading()
    {
        m_PerformReading = true;
        Unblock();
    }

    void SoilSensorTask::OnSoilSensorDataRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
    {
        SoilSensorTask* self{static_cast<SoilSensorTask*>(eventHandlerArg)};
        self->WakeForReading();
    }
}