#include "SstIdleState.h"

#include "esp_log.h"
#include "Tasks/SoilSensorTask.h"
#include "State/SoilSensorTaskState/SoilSensorTaskState.h"

namespace gg
{
    static const char* TAG = "Idle State";

    SstIdleState::SstIdleState(StateMachineTask* stateMachine)
        : SstBaseState(stateMachine)
    {}

    void SstIdleState::Update()
    {
        if (m_SoilSensorTask->InitiateSampling())
        {
            ESP_LOGI(TAG, "Initiating");

            // Switch to prepare state with no delay
            m_SoilSensorTask->SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Prepare), m_PrepareDelay);

            // Reset flag
            m_SoilSensorTask->ResetInitiateSamplingFlag();
        }
    }
}