#include "DataProcessTask.h"

#include "esp_log.h"
#include "Events/Events.h"

namespace gg
{
    static const char* TAG = "Data Processing Task";
    
    void DataProcessTask::Start()
    {
        // Task creation
        TaskConfig taskConfig{};
        taskConfig.name = "Data Process Task";
        taskConfig.stackSize = 2048;
        taskConfig.priority = 8;
        CreateTask(TAG, taskConfig);

        // Initialize semaphore
        m_Lock = xSemaphoreCreateMutex();

        // Subscribe event handlers to their event
        SubscribeToEvent(this, OnSoilSensorDataShared, MAIN_EVENTS, static_cast<int32_t>(MainEvents::ShareSensorOutput));
    }
    void DataProcessTask::Execute()
    {
        ESP_LOGI(TAG, "Executing");

        m_SampleData.remainingSamples = 10;
        m_SampleData.delayBetweenSamplesMs = 100;
        EventBus::Get().PostEvent<SampleSession>(m_SampleData, MAIN_EVENTS, static_cast<int32_t>(MainEvents::RequestSensorData));
    }

    void DataProcessTask::OnSoilSensorDataShared(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
    {
        float data{*reinterpret_cast<float*>(eventData)};
        ESP_LOGI(TAG, "Event received: %.2f", data);
    }
}