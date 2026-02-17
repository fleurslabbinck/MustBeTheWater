#ifndef SOIL_SENSOR_TASK_H
#define SOIL_SENSOR_TASK_H

#include <memory>
#include <atomic>
#include <queue>
#include <optional>
#include "Tasks/Core/StateMachineTask.h"
#include "Events/Core/Listener.h"
#include "Components/SoilSensor.h"
#include "DataProcessTask.h"

namespace gg
{
    class SoilSensorTask final : public StateMachineTask, public Listener
    {
    public:
        SoilSensorTask() = default;
        SoilSensorTask(const SoilSensorTask&) = delete;
        SoilSensorTask(SoilSensorTask&&) = delete;
        SoilSensorTask& operator=(const SoilSensorTask&) = delete;
        SoilSensorTask& operator=(SoilSensorTask&&) = delete;

        void Start();
        void SetInitiateSamplingFlag() {m_InitiateSampling.store(true, std::memory_order_relaxed);}
        void ResetInitiateSamplingFlag() {m_InitiateSampling.store(false, std::memory_order_relaxed);}
        void Sample();

        bool InitiateSampling() const {return m_InitiateSampling.load(std::memory_order_relaxed);}
        SoilSensor* GetSoilSensor() const {return m_SoilSensor.get();}
        std::optional<uint32_t> TryGetSampleQueueItem();

    private:
        static constexpr int32_t m_MaxLockWaitTime{5000};
        float m_Data{};
        std::atomic<bool> m_InitiateSampling{false};
        std::unique_ptr<SoilSensor> m_SoilSensor{nullptr};
        std::queue<uint32_t> m_SampleQueue{};
        SemaphoreHandle_t m_Lock{nullptr};

        void InitializeStateMachine() override;
        void PrepareForSampling(const SampleData& sampleData);

        static void OnSoilSensorDataRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
    };
}
#endif