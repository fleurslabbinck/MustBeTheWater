#ifndef SOIL_SENSOR_TASK_H
#define SOIL_SENSOR_TASK_H

#include <memory>
#include "Tasks/Core/NotificationTask.h"
#include "Components/SoilSensor.h"
#include "Events/Core/Listener.h"

namespace gg
{
    class SoilSensorTask final : public NotificationTask, public Listener
    {
    public:
        SoilSensorTask() = default;
        SoilSensorTask(const SoilSensorTask&) = delete;
        SoilSensorTask(SoilSensorTask&&) = delete;
        SoilSensorTask& operator=(const SoilSensorTask&) = delete;
        SoilSensorTask& operator=(SoilSensorTask&&) = delete;

        void Start();
        void WakeForReading();

    private:
        bool m_PerformReading{false};
        float m_Data{};
        std::unique_ptr<SoilSensor> m_SoilSensor{nullptr};

        void Execute() override;

        static void OnSoilSensorDataRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
    };
}
#endif