#include "BlinkLedTask.h"

#include "Components/PowerSupply.h"

namespace gg
{
    BlinkLedTask::BlinkLedTask(uint32_t waitTime)
        : NotificationTask(waitTime)
    {}

    void BlinkLedTask::Start(const TaskAssembly& taskAssembly, gpio_num_t gpioPin)
    {
        Init(taskAssembly);
        m_PowerSupply = std::make_unique<PowerSupply>(gpioPin);
    }

    void BlinkLedTask::Execute()
    {
        if (m_Blink)
        {
            m_PowerSupply->Enable();
        }
        else
        {
            m_PowerSupply->Disable();
        }

        m_Blink = !m_Blink;
    }
}