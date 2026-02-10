#include "BlinkLedTask.h"

#include "Components/PowerSupply.h"

namespace gg
{
    BlinkLedTask::BlinkLedTask(uint32_t waitTime)
        : NotificationTask(waitTime)
    {}

    void BlinkLedTask::Start()
    {
        // Task creation
        TaskConfig taskConfig{};
        taskConfig.name = "Blink LED Task";
        taskConfig.stackSize = 2048;
        taskConfig.priority = 5;
        CreateTask(taskConfig);

        m_PowerSupply = std::make_unique<PowerSupply>(GPIO_NUM_2);
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