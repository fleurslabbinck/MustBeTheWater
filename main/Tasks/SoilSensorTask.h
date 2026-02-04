#ifndef SOIL_SENSOR_TASK_H
#define SOIL_SENSOR_TASK_H

#include "Tasks/Core/PeriodicNotificationTask.h"
#include "Components/SoilSensor.h"

namespace gg
{
    class SoilSensorTask final : public PeriodicNotificationTask
    {
    public:
        SoilSensorTask(gpio_num_t gpio, adc_channel_t adcChannel, int dryReading, int wetReading, uint32_t startupDelay, uint32_t waitTime);
        SoilSensorTask(const SoilSensorTask&) = delete;
        SoilSensorTask(SoilSensorTask&&) = delete;
        SoilSensorTask& operator=(const SoilSensorTask&) = delete;
        SoilSensorTask& operator=(SoilSensorTask&&) = delete;

        void Start();

    private:
        SoilSensor m_SoilSensor;

        void Execute() override;
    };
}
#endif