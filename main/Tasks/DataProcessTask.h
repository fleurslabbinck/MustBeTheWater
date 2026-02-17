#ifndef DATA_PROCESS_TASK_H
#define DATA_PROCESS_TASK_H

#include "Tasks/Core/PeriodicNotificationTask.h"
#include "Events/Core/Listener.h"
#include "Helpers/RingBuffer.h"

namespace gg
{
    struct SampleData
    {
        uint8_t amount{};
        uint32_t delay{};
    };

    class DataProcessTask final : public PeriodicNotificationTask, public Listener
    {
    public:
        DataProcessTask() = default;
        DataProcessTask(const DataProcessTask&) = delete;
        DataProcessTask(DataProcessTask&&) = delete;
        DataProcessTask& operator=(const DataProcessTask&) = delete;
        DataProcessTask& operator=(DataProcessTask&&) = delete;

        void Start();

    private:
        SampleData m_SampleData{};
        RingBuffer<float, 10> m_DataQueue{};

        void Execute() override;

        static void OnSoilSensorDataShared(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
    };
}
#endif