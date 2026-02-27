#include "SstResetState.h"

#include "esp_log.h"
#include "Tasks/SoilSensorTask.h"
#include "State/SoilSensorTaskState/SoilSensorTaskState.h"

namespace gg
{
    SstResetState::SstResetState(StateMachineTask* stateMachine)
        : SstBaseState(stateMachine)
    {}

    void SstResetState::Update()
    {
        m_SoilSensorTask->PowerOffSoilSensor();

        // Switch to ready state and reset delay
        m_SoilSensorTask->SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Idle));
    }
}