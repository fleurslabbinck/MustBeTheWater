#include "Program.h"

#include "SystemTasks.h"

namespace gg
{
    // Start tasks
    void Program::Init() const
    {
        SystemTasks::s_SoilSensorTask.Start();
    }
}