#include "SstResetState.h"

#include "esp_log.h"
#include "Tasks/SoilSensorTask.h"
#include "State/SoilSensorTaskState/SoilSensorTaskState.h"

namespace gg
{
    static const char* TAG = "Reset";

    SstResetState::SstResetState(StateMachineTask* stateMachine)
        : SstBaseState(stateMachine)
    {}

    void SstResetState::Update()
    {
        ESP_LOGI(TAG, "Stopping soil sensor power");

        SoilSensor* soilSensor{m_SoilSensorTask->GetSoilSensor()};

        // Stop powering the soil sensor
        soilSensor->RemovePower();

        // Switch to ready state and reset delay
        m_SoilSensorTask->SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Idle));
    }
}