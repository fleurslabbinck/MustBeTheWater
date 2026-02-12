#ifndef DATA_PROCESS_TASK_H
#define DATA_PROCESS_TASK_H

#include "Tasks/Core/NotificationTask.h"
#include "Events/Core/Listener.h"

namespace gg
{
    class DataProcessTask final : public NotificationTask, public Listener
    {
    public:
        DataProcessTask() = default;
        DataProcessTask(const DataProcessTask&) = delete;
        DataProcessTask(DataProcessTask&&) = delete;
        DataProcessTask& operator=(const DataProcessTask&) = delete;
        DataProcessTask& operator=(DataProcessTask&&) = delete;

        void Start();

    private:
        void Execute() override;

        static void OnSoilSensorDataShared(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
    };
}
#endif