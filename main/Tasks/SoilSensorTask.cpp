#include "SoilSensorTask.h"

#include "esp_log.h"
#include "Events/Events.h"

namespace gg
{
    static const char* TAG = "SoilSensorTask";

    void SoilSensorTask::Start()
    {
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

    void SoilSensorTask::Execute()
    {
        if (m_Sample.load(std::memory_order_relaxed))
        {
            m_TaskState = TaskState::Preparing;
            m_Sample.store(false, std::memory_order_relaxed);
        }

        switch (m_TaskState)
        {
        case TaskState::Preparing:
            // Start powering the sensor and set delay
            m_SoilSensor->ApplyPower();
            ChangeWaitTime(m_SoilSensor->GetPoweringDelay());
            m_TaskState = TaskState::Ready;
            break;
        case TaskState::Ready:
            {
                bool shouldSample{false};
                uint32_t newWaitTime{};

                xSemaphoreTake(m_Lock, portMAX_DELAY);

                if (!m_SampleQueue.empty())
                {
                    shouldSample = true;
                    newWaitTime = m_SampleQueue.front();
                    m_SampleQueue.pop();
                }
                else
                {
                    m_TaskState = TaskState::Resetting;
                }

                xSemaphoreGive(m_Lock);

                if (shouldSample)
                {
                    Sample();

                    if (newWaitTime > 0)
                    {
                        ChangeWaitTime(newWaitTime);
                    }
                    else
                    {
                        ResetWaitTime();
                    }
                }
            }
            break;
        case TaskState::Resetting:
            // Stop powering the sensor
            m_SoilSensor->RemovePower();
            m_TaskState = TaskState::Idle;
            ResetWaitTime();
            break;
        default:
            break;
        }
    }

    // Wake task to allow sensor reading to happen
    void SoilSensorTask::PrepareForSampling(const SampleData& sampleData)
    {
        xSemaphoreTake(m_Lock, portMAX_DELAY);

        m_Sample.store(true, std::memory_order_relaxed);

        for (uint8_t i{}; i < sampleData.amount; ++i)
        {
            m_SampleQueue.push(sampleData.delay);
        }

        xSemaphoreGive(m_Lock);

        Unblock();
    }

    void SoilSensorTask::Sample()
    {
        m_Data = m_SoilSensor->GetSample();
        EventBus::Get().PostEvent<float>(m_Data, MAIN_EVENTS, static_cast<int32_t>(MainEvents::ShareSensorData));
    }

    void SoilSensorTask::OnSoilSensorDataRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
    {
        SoilSensorTask* self{static_cast<SoilSensorTask*>(eventHandlerArg)};
        SampleData sampleData{*reinterpret_cast<SampleData*>(eventData)};
        self->PrepareForSampling(sampleData);
    }
}