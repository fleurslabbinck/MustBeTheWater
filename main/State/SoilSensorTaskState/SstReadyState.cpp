#include "SstReadyState.h"

#include "esp_log.h"
#include "Tasks/SoilSensorTask.h"
#include "State/SoilSensorTaskState/SoilSensorTaskState.h"

namespace gg
{
    static const char* TAG = "Ready State";

    SstReadyState::SstReadyState(StateMachineTask* stateMachine)
        : SstBaseState(stateMachine)
    {}

    void SstReadyState::Update()
    {
        // Try to get the first item of the sample queue
        std::optional<uint32_t> sampleQueueItem{m_SoilSensorTask->TryGetSampleQueueItem()};
        if (sampleQueueItem.has_value())
        {
            ESP_LOGI(TAG, "Sampling, delay value: %d", sampleQueueItem.value());
            // Sample if item is valid
            m_SoilSensorTask->Sample();

            // Switch to same state to set delay acquired from sample queue
            m_SoilSensorTask->SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Ready), sampleQueueItem.value());
        }
        else
        {
            ESP_LOGI(TAG, "Done sampling");
            // Switch to reset state without delay
            m_SoilSensorTask->SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Reset), 0);
        }
    }
}