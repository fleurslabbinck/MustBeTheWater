#ifndef SYSTEM_TASKS_H
#define SYSTEM_TASKS_H

#include "Tasks/SoilSensorTask.h"
#include "Tasks/DataProcessTask.h"
#include "Tasks/BlinkLedTask.h"

namespace gg
{
    // Register all tasks
    struct SystemTasks
    {
        inline static SoilSensorTask s_SoilSensorTask{};
    };
}
#endif