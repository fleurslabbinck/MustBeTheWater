#include "BlinkLedTask.h"

namespace gg
{
    BlinkLedTask::BlinkLedTask(uint8_t gpioPin, uint32_t waitTime)
    : NotificationTask(waitTime), m_Led{gpioPin}
    {}

    void BlinkLedTask::Start()
    {
        Init("Blink LED Task", 2048, 5);
    }

    void BlinkLedTask::Execute()
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