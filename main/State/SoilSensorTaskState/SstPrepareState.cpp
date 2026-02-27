#include "SstPrepareState.h"

#include "esp_log.h"
#include "Tasks/SoilSensorTask.h"
#include "State/SoilSensorTaskState/SoilSensorTaskState.h"

namespace gg
{
    SstPrepareState::SstPrepareState(StateMachineTask* stateMachine)
        : SstBaseState(stateMachine)
    {}

    void SstPrepareState::Update()
    {
        // Prepare for sample session
        m_SoilSensorTask->AssignActiveSampleSession();
        m_SoilSensorTask->PowerOnSoilSensor();

        // Switch to ready state with powering delay
        m_SoilSensorTask->SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Ready) , m_SoilSensorTask->GetSoilSensorPoweringDelay());
    }
}