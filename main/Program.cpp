#include "Program.h"

namespace gg
{
    SoilSensorTask Program::m_SoilSensorTask{};

    // Start tasks
    void Program::Init()
    {
        m_SoilSensorTask.Start();
    }
}