#include "Program.h"

#include "SystemTasks.h"
#include "Events/Events.h"

ESP_EVENT_DEFINE_BASE(MAIN_EVENTS);

namespace gg
{
    // Start tasks
    void Program::Init() const
    {
        SystemTasks::s_SoilSensorTask.Start();
        SystemTasks::s_DataProcessTask.Start();
    }
}