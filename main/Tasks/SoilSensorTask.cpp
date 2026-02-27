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

    SoilSensorTask::SoilSensorTask()
        : m_SampleSessionQueue{xQueueCreate(5, sizeof(SampleSession))}
    {}

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
    void SoilSensorTask::PrepareSampleSession(const SampleSession& sampleSession)
    {
        // Add sample session to queue
        xQueueSend(m_SampleSessionQueue, &sampleSession, 0);

        // Wake task to start sampling behavior
        Unblock();
    }

    // Checks if there is at least 1 sample session in the queue
    bool SoilSensorTask::HasRemainingSampleSessions() const
    {
        return uxQueueMessagesWaiting(m_SampleSessionQueue) > 0;
    }

    // Assigns the front item from the sample queue to active sample session
    void SoilSensorTask::AssignActiveSampleSession()
    {
        SampleSession newSession{};
        xQueueReceive(m_SampleSessionQueue, &newSession, 0);
        m_ActiveSampleSession = newSession;
    }

    // Get a sample from the soil sensor and update active sample session status
    void SoilSensorTask::Sample()
    {
        m_SoilSensorOutput = m_SoilSensor->GetSample();

        // Decrement remaining samples and reset active session when decremented to 0
        --m_ActiveSampleSession.value().remainingSamples;
        if (m_ActiveSampleSession.value().remainingSamples == 0)
        {
            m_ActiveSampleSession = std::nullopt;
        }

        EventBus::Get().PostEvent<float>(m_SoilSensorOutput, MAIN_EVENTS, static_cast<int32_t>(MainEvents::ShareSensorOutput));
    }

    // Try to get delay between samples from active sample session
    std::optional<uint32_t> SoilSensorTask::TryGetSampleSessionDelay() const
    {
        if (m_ActiveSampleSession.has_value())
        {
            return m_ActiveSampleSession.value().delayBetweenSamplesMs;
        }

        return std::nullopt;
    }

    void SoilSensorTask::OnSoilSensorDataRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
    {
        // Get soil sensor task instance
        SoilSensorTask* self{static_cast<SoilSensorTask*>(eventHandlerArg)};

        // Interpret data as sample data
        SampleSession sampleSession{*reinterpret_cast<SampleSession*>(eventData)};

        ESP_LOGI(TAG, "Sample Requested");

        // Setup sampling process
        self->PrepareSampleSession(sampleSession);
    }
}