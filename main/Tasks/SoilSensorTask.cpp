#include "SoilSensorTask.h"

#include "esp_log.h"

namespace gg
{
    constexpr uint8_t BLINK_GPIO{2};
    constexpr uint32_t STEP_MS{1000};

    SoilSensorTask::SoilSensorTask()
    : NotificationTask(STEP_MS), m_Led{Led(BLINK_GPIO)}
    {}

    void SoilSensorTask::Start()
    {
        Init("Blink Task", 2048, 5);
    }

    void SoilSensorTask::Execute()
    {
        if (m_Blink)
        {
            m_Led.TurnOn();
        }
        else
        {
            m_Led.TurnOff();
        }

        m_Blink = !m_Blink;
    }
}