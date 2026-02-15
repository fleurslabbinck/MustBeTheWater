#include "SoilSensorTask.h"

#include "esp_log.h"
#include "Events/Events.h"

namespace gg
{
    static const char* TAG = "SoilSensor";

    void SoilSensorTask::Start()
    {
        // Task creation
        TaskConfig taskConfig{};
        taskConfig.name = "Soil Sensor Task";
        taskConfig.stackSize = 6144;
        taskConfig.priority = 10;
        CreateTask(taskConfig);

        // Soil sensor initialization
        SoilSensorConfig soilSensorConfig{};
        soilSensorConfig.gpio = GPIO_NUM_2;
        soilSensorConfig.adcChannel = ADC_CHANNEL_0;
        soilSensorConfig.dryRef = 2770;
        soilSensorConfig.wetRef = 430;
        soilSensorConfig.poweringDelay = 500;
        m_SoilSensor = std::make_unique<SoilSensor>(soilSensorConfig);

        // Initialize semaphore
        m_QueueLock = xSemaphoreCreateMutex();

        // Subscribe event handlers to their event
        SubscribeToEvent(this, OnSoilSensorDataRequested, MAIN_EVENTS, static_cast<int32_t>(MainEvents::RequestSensorData));
    }

    void SoilSensorTask::Execute()
    {
        ESP_LOGI(TAG, "Executing task");
        switch (m_TaskState)
        {
        case TaskState::Preparing:
            // Start powering the sensor and set delay
            m_SoilSensor->ApplyPower();
            ChangeWaitTime(m_SoilSensor->GetPoweringDelay());
            ESP_LOGI(TAG, "Powering sensor");
            m_TaskState = TaskState::Ready;
            break;
        case TaskState::Ready:
            {
                bool shouldSample{false};
                uint32_t newWaitTime{};

                //xSemaphoreTake(m_QueueLock, portMAX_DELAY);

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

                //xSemaphoreGive(m_QueueLock);

                if (shouldSample)
                {
                    Sample();
                    ESP_LOGI(TAG, "Sampling");

                    if (newWaitTime > 0)
                    {
                        ChangeWaitTime(newWaitTime);
                    }
                }
            }
            break;
        case TaskState::Resetting:
            // Stop powering the sensor
            m_SoilSensor->RemovePower();
            m_TaskState = TaskState::Idle;
            ESP_LOGI(TAG, "Removing sensor power");
            break;
        default:
            break;
        }
    }

    // Wake task to allow sensor reading to happen
    void SoilSensorTask::PrepareForSampling(const SampleData& sampleData)
    {
        xSemaphoreTake(m_QueueLock, portMAX_DELAY);

        m_TaskState = TaskState::Preparing;

        for (uint8_t i{}; i < sampleData.amount; ++i)
        {
            m_SampleQueue.push(sampleData.delay);
        }

        xSemaphoreGive(m_QueueLock);

        ESP_LOGI(TAG, "Preparing to sample");

        Unblock();
    }

    void SoilSensorTask::Sample()
    {
        m_Data = m_SoilSensor->GetSample();
        EventBus::Get().PostEvent<float>(m_Data, MAIN_EVENTS, static_cast<int32_t>(MainEvents::ShareSensorData));

        ESP_LOGI(TAG, "reading: %.2f", m_Data);
    }

    void SoilSensorTask::OnSoilSensorDataRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
    {
        SoilSensorTask* self{static_cast<SoilSensorTask*>(eventHandlerArg)};
        SampleData sampleData{*reinterpret_cast<SampleData*>(eventData)};
        self->PrepareForSampling(sampleData);
        ESP_LOGI(TAG, "Received sample request");
    }
}