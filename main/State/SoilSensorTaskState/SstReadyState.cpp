#include "SstReadyState.h"

#include "esp_log.h"
#include "Tasks/SoilSensorTask.h"
#include "State/SoilSensorTaskState/SoilSensorTaskState.h"

namespace gg
{
    SstReadyState::SstReadyState(StateMachineTask* stateMachine)
        : SstBaseState(stateMachine)
    {}

    void SstReadyState::Update()
    {
        // Sample and update active session
        m_SoilSensorTask->Sample();

        // Try to get the delay between samples from updated session
        std::optional<uint32_t> delay{m_SoilSensorTask->TryGetSampleSessionDelay()};

        if (delay.has_value())
        {
            // Set delay acquired from active session
            m_SoilSensorTask->SetDelay(delay.value());
        }
        else
        {
            // Switch to reset state without delay
            m_SoilSensorTask->SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Reset), 0);
        }
    }
}