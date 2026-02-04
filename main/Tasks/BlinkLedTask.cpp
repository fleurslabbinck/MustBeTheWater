#include "BlinkLedTask.h"

namespace gg
{
    BlinkLedTask::BlinkLedTask(gpio_num_t gpioPin, uint32_t waitTime)
        : NotificationTask(waitTime), m_PowerSupply{gpioPin}
    {}

    void BlinkLedTask::Start()
    {
        Init("Blink LED Task", 2048, 5);
    }

    void BlinkLedTask::Execute()
    {
        if (m_Blink)
        {
            m_PowerSupply.Enable();
        }
        else
        {
            m_PowerSupply.Disable();
        }

        m_Blink = !m_Blink;
    }
}