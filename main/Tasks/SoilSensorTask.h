#ifndef SOIL_SENSOR_TASK_H
#define SOIL_SENSOR_TASK_H

#include <memory>

#include "Tasks/Core/PeriodicNotificationTask.h"
#include "Components/SoilSensor.h"
#include "Events/Core/Sender.h"
#include "Events/Core/Listener.h"
#include "Events/Events.h"

namespace gg
{
    class SoilSensorTask final : public PeriodicNotificationTask, public Sender
    {
    public:
        SoilSensorTask();
        SoilSensorTask(const SoilSensorTask&) = delete;
        SoilSensorTask(SoilSensorTask&&) = delete;
        SoilSensorTask& operator=(const SoilSensorTask&) = delete;
        SoilSensorTask& operator=(SoilSensorTask&&) = delete;

        void Start();

    private:
        float m_Data{};
        std::unique_ptr<SoilSensor> m_SoilSensor{nullptr};

        void Execute() override;
    };
}
#endif