#include "Program.h"

#include "SystemTasks.h"

ESP_EVENT_DEFINE_BASE(MAIN_EVENTS);

namespace gg
{
    // Start tasks
    void Program::Init() const
    {
        SystemTasks::s_SoilSensorTask.Start();
        SystemTasks::s_DataProcessTask.Start();
        SystemTasks::s_DataProcessTask.SubscribeToEvent(
            SystemTasks::s_SoilSensorTask,
            SystemTasks::s_DataProcessTask.OnSoilSensorData,
            MAIN_EVENTS,
            static_cast<int32_t>(MainEvents::SensorData)
        );
    }
}