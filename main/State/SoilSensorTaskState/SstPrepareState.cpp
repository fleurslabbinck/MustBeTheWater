#include "SstPrepareState.h"

#include "esp_log.h"
#include "Tasks/SoilSensorTask.h"
#include "State/SoilSensorTaskState/SoilSensorTaskState.h"

namespace gg
{
    static const char* TAG = "Prepare State";

    SstPrepareState::SstPrepareState(StateMachineTask* stateMachine)
        : SstBaseState(stateMachine)
    {}

    void SstPrepareState::Update()
    {
        ESP_LOGI(TAG, "Powering soil sensor");

        SoilSensor* soilSensor{m_SoilSensorTask->GetSoilSensor()};

        // Start powering the soil sensor
        soilSensor->ApplyPower();

        // Switch to ready state with powering delay
        m_SoilSensorTask->SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Ready) , soilSensor->GetPoweringDelay());
    }
}