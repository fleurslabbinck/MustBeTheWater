#ifndef SOIL_SENSOR_TASK_H
#define SOIL_SENSOR_TASK_H

#include <memory>
#include <atomic>
#include <queue>
#include "Tasks/Core/NotificationTask.h"
#include "Components/SoilSensor.h"
#include "Events/Core/Listener.h"
#include "DataProcessTask.h"

namespace gg
{
    class SoilSensorTask final : public NotificationTask, public Listener
    {
        enum TaskState : uint8_t
        {
            Idle,
            Preparing,
            Ready,
            Resetting
        };

    public:
        SoilSensorTask() = default;
        SoilSensorTask(const SoilSensorTask&) = delete;
        SoilSensorTask(SoilSensorTask&&) = delete;
        SoilSensorTask& operator=(const SoilSensorTask&) = delete;
        SoilSensorTask& operator=(SoilSensorTask&&) = delete;

        void Start();

    private:
        TaskState m_TaskState{TaskState::Idle};
        float m_Data{};
        std::atomic<bool> m_Sample{false};
        std::unique_ptr<SoilSensor> m_SoilSensor{nullptr};
        std::queue<uint32_t> m_SampleQueue{};
        SemaphoreHandle_t m_Lock{nullptr};

        void Execute() override;
        void PrepareForSampling(const SampleData& sampleData);
        void Sample();

        static void OnSoilSensorDataRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
    };
}
#endif