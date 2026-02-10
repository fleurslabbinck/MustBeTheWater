#include "DataProcessTask.h"

#include "esp_log.h"

namespace gg
{
    static const char* TAG = "Data Processing";
    
    void DataProcessTask::Start()
    {
        // Task creation
        TaskConfig taskConfig{};
        taskConfig.name = "Data Process Task";
        taskConfig.stackSize = 2048;
        taskConfig.priority = 8;
        CreateTask(taskConfig);
    }

    void DataProcessTask::Execute()
    {

    }

    void DataProcessTask::OnSoilSensorData(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
    {
        float data{*reinterpret_cast<float*>(eventData)};
        ESP_LOGI(TAG, "Event received: %.2f", data);
    }
}