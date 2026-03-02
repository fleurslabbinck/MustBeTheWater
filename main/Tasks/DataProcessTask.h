#ifndef DATA_PROCESS_TASK_H
#define DATA_PROCESS_TASK_H

#include "Tasks/Core/PeriodicNotificationTask.h"
#include "Events/Core/Listener.h"
#include "Helpers/RingBuffer.h"

namespace gg
{
    struct SampleSession
    {
        uint8_t remainingSamples{};
        uint32_t delayBetweenSamplesMs{};
    };

    class DataProcessTask final : public PeriodicNotificationTask, public Listener
    {
        enum class DataProcessBits : uint32_t
        {
            Calibration = BIT0,
            DataShared = BIT1
        };

    public:
        DataProcessTask() = default;
        DataProcessTask(const DataProcessTask&) = delete;
        DataProcessTask(DataProcessTask&&) = delete;
        DataProcessTask& operator=(const DataProcessTask&) = delete;
        DataProcessTask& operator=(DataProcessTask&&) = delete;

        void Start();

    private:
        static constexpr size_t s_DataQueueSize{10};
        static constexpr uint32_t s_MaxBlockTime{500};
        float m_AverageSensorValue{};
        SampleSession m_CalibrationSession{};
        SemaphoreHandle_t m_Lock{nullptr};
        RingBuffer<float, s_DataQueueSize> m_DataQueue{};

        void Execute() override;
        void StartCalibration();
        void BroadcastAverageSensorValue();
        void HandleDataShared(float sensorData);

        std::optional<float> CalculateAverageSensorValue() const;

        static void OnSoilSensorCalibrationRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
        static void OnSoilSensorDataShared(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
    };
}
#endif