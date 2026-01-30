#ifndef SOIL_SENSOR_TASK_H
#define SOIL_SENSOR_TASK_H

#include "Tasks/Core/NotificationTask.h"
#include "Components/Led.h"

namespace gg
{
    class SoilSensorTask final : public NotificationTask
    {
    public:
        SoilSensorTask(uint8_t gpioPin, uint32_t waitTime);
        SoilSensorTask(const SoilSensorTask&) = delete;
        SoilSensorTask(SoilSensorTask&&) = delete;
        SoilSensorTask& operator=(const SoilSensorTask&) = delete;
        SoilSensorTask& operator=(SoilSensorTask&&) = delete;

        void Start();

    private:
        void Execute() override;
    };
}
#endif