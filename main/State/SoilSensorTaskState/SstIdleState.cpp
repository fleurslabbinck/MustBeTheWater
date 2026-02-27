#include "SstIdleState.h"

#include "esp_log.h"
#include "Tasks/SoilSensorTask.h"
#include "State/SoilSensorTaskState/SoilSensorTaskState.h"

namespace gg
{
    SstIdleState::SstIdleState(StateMachineTask* stateMachine)
        : SstBaseState(stateMachine)
    {}

    void SstIdleState::Update()
    {
        // Check if session is available
        if (m_SoilSensorTask->HasRemainingSampleSessions())
        {
            // Switch to prepare state with no delay
            m_SoilSensorTask->SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Prepare), m_PrepareDelay);
        }
    }
}