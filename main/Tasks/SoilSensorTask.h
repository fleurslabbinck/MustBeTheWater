#ifndef SOIL_SENSOR_TASK_H
#define SOIL_SENSOR_TASK_H

#include <memory>
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
        SoilSensorTask();
        SoilSensorTask(const SoilSensorTask&) = delete;
        SoilSensorTask(SoilSensorTask&&) = delete;
        SoilSensorTask& operator=(const SoilSensorTask&) = delete;
        SoilSensorTask& operator=(SoilSensorTask&&) = delete;

        void Start();
        void AssignActiveSampleSession();
        void Sample();
        void PowerOnSoilSensor() const {m_SoilSensor->ApplyPower();}
        void PowerOffSoilSensor() const {m_SoilSensor->RemovePower();}

        bool HasRemainingSampleSessions() const;
        uint32_t GetSoilSensorPoweringDelay() const {return m_SoilSensor->GetPoweringDelay();}
        std::optional<uint32_t> TryGetSampleSessionDelay() const;

    private:
        float m_SoilSensorOutput{};
        std::optional<SampleSession> m_ActiveSampleSession{std::nullopt};
        std::unique_ptr<SoilSensor> m_SoilSensor{nullptr};
        QueueHandle_t m_SampleSessionQueue{nullptr};

        void InitializeStateMachine() override;
        void PrepareSampleSession(const SampleSession& sampleSession);

        static void OnSoilSensorDataRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
    };
}
#endif