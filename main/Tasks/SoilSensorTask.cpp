#include "SoilSensorTask.h"

#include "esp_log.h"
#include "State/SoilSensorTaskState/SoilSensorTaskState.h"
#include "State/SoilSensorTaskState/SstIdleState.h"
#include "State/SoilSensorTaskState/SstPrepareState.h"
#include "State/SoilSensorTaskState/SstReadyState.h"
#include "State/SoilSensorTaskState/SstResetState.h"
#include "Events/Events.h"

namespace gg
{
    static const char* TAG = "Soil Sensor Task";

    void SoilSensorTask::Start()
    {
        // Initialize states first
        InitializeStateMachine();

        // Task creation
        TaskConfig taskConfig{};
        taskConfig.name = "Soil Sensor Task";
        taskConfig.stackSize = 6144;
        taskConfig.priority = 10;
        CreateTask(TAG, taskConfig);

        // Soil sensor initialization
        SoilSensorConfig soilSensorConfig{};
        soilSensorConfig.gpio = GPIO_NUM_2;
        soilSensorConfig.adcChannel = ADC_CHANNEL_0;
        soilSensorConfig.dryRef = 2770;
        soilSensorConfig.wetRef = 430;
        soilSensorConfig.poweringDelay = 500;
        m_SoilSensor = std::make_unique<SoilSensor>(soilSensorConfig);

        // Initialize semaphore
        m_Lock = xSemaphoreCreateMutex();

        // Subscribe event handlers to their event
        SubscribeToEvent(this, OnSoilSensorDataRequested, MAIN_EVENTS, static_cast<int32_t>(MainEvents::RequestSensorData));
    }

    void SoilSensorTask::InitializeStateMachine()
    {
        // Add all states under their state id
        AddState<SstIdleState>(static_cast<uint8_t>(SoilSensorTaskState::Idle));
        AddState<SstPrepareState>(static_cast<uint8_t>(SoilSensorTaskState::Prepare));
        AddState<SstReadyState>(static_cast<uint8_t>(SoilSensorTaskState::Ready));
        AddState<SstResetState>(static_cast<uint8_t>(SoilSensorTaskState::Reset));

        // Initialize starting state
        SwitchState(static_cast<uint8_t>(SoilSensorTaskState::Idle));
    }

    // Wake task to allow sensor reading to happen
    void SoilSensorTask::PrepareForSampling(const SampleData& sampleData)
    {
        SetInitiateSamplingFlag();

        // Lock semaphore for a max amount of wait time
        xSemaphoreTake(m_Lock, pdMS_TO_TICKS(m_MaxLockWaitTime));

        for (uint8_t i{}; i < sampleData.amount; ++i)
        {
            m_SampleQueue.push(sampleData.delay);
        }

        // Release semaphore
        xSemaphoreGive(m_Lock);

        // Wake task to start sampling behavior
        Unblock();

    }

    // Attempts to get the front item from the sample queue
    std::optional<uint32_t> SoilSensorTask::TryGetSampleQueueItem()
    {
        std::optional<uint32_t> sampleQueueItem{};

        // Lock semaphore for a max amount of wait time
        xSemaphoreTake(m_Lock, pdMS_TO_TICKS(m_MaxLockWaitTime));

        if (!m_SampleQueue.empty())
        {
            sampleQueueItem = m_SampleQueue.front();
            m_SampleQueue.pop();
        }
        else
        {
            sampleQueueItem = std::nullopt;
        }

        // Release semaphore
        xSemaphoreGive(m_Lock);

        return sampleQueueItem;
    }

    // Get a sample from the soil sensor
    void SoilSensorTask::Sample()
    {
        m_Data = m_SoilSensor->GetSample();
        EventBus::Get().PostEvent<float>(m_Data, MAIN_EVENTS, static_cast<int32_t>(MainEvents::ShareSensorData));
    }

    void SoilSensorTask::OnSoilSensorDataRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
    {
        // Get soil sensor task instance
        SoilSensorTask* self{static_cast<SoilSensorTask*>(eventHandlerArg)};

        // Interpret data as sample data
        SampleData sampleData{*reinterpret_cast<SampleData*>(eventData)};

        ESP_LOGI(TAG, "Sample Requested");

        // Setup sampling process
        self->PrepareForSampling(sampleData);
    }
}