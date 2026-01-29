#include "SoilSensorTask.h"

#include "esp_log.h"

namespace gg
{
    SoilSensorTask::SoilSensorTask(uint8_t gpioPin, uint32_t waitTime)
    : NotificationTask(waitTime)
    {}

    void SoilSensorTask::Start()
    {
        Init("Soil Sensor Task", 2048, 5);
    }

    void SoilSensorTask::Execute()
    {
        
    }
}