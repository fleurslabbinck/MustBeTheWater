#include "Program.h"

#include "SystemTasks.h"

namespace gg
{
    // Start tasks
    void Program::Init() const
    {
        SystemTasks::s_BlinkLedTaskA.Start();
        SystemTasks::s_BlinkLedTaskB.Start();
    }
}