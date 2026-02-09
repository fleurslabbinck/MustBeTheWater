#include "Program.h"

#include "SystemTasks.h"

namespace gg
{
    // Start tasks
    void Program::Init() const
    {
        const TaskAssembly soilSensorTaskAssembly{"Soil Sensor Task", 6144, 10, CoreSelect::None};
        const TaskAssembly eventLoopTaskAssembly{"Soil Sensor Event Loop", 3084, 5, CoreSelect::None};
        const SoilSensorAssembly soilSensorAssembly{GPIO_NUM_2, ADC_CHANNEL_0, 2770, 430, 500};

        SystemTasks::s_SoilSensorTask.Start(soilSensorTaskAssembly, eventLoopTaskAssembly, soilSensorAssembly, 5);
    }
}