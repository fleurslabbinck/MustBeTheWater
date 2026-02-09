#include "SoilSensorTask.h"

#include "esp_log.h"
#include "Components/SoilSensor.h"

namespace gg
{
    static const char* TAG = "SoilSensor";

    SoilSensorTask::SoilSensorTask(uint32_t waitTime)
        : PeriodicNotificationTask(waitTime)
    {}

    void SoilSensorTask::Start(const TaskAssembly& taskAssembly, const TaskAssembly& eventLoopTaskAssembly, const SoilSensorAssembly& soilSensorAssembly, int32_t queueSize)
    {
        Init(taskAssembly);
        CreateEventLoop(eventLoopTaskAssembly, queueSize);
        m_SoilSensor = std::make_unique<SoilSensor>(soilSensorAssembly);
    }

    void SoilSensorTask::Execute()
    {
        float reading{m_SoilSensor->GetMoistureReading()};
        ESP_LOGI(TAG, "reading: %.2f", reading);
    }
}