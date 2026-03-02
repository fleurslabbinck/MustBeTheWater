#include "DataProcessTask.h"

#include "esp_log.h"
#include "Events/Events.h"

namespace gg
{
    static const char* TAG = "Data Processing Task";
    
    void DataProcessTask::Start()
    {
        // Assemble calibration session
        m_CalibrationSession.remainingSamples = 10;
        m_CalibrationSession.delayBetweenSamplesMs = 100;

        // Task creation
        TaskConfig taskConfig{};
        taskConfig.name = "Data Process Task";
        taskConfig.stackSize = 2048;
        taskConfig.priority = 8;
        CreateTask(TAG, taskConfig);

        // Initialize semaphore
        m_Lock = xSemaphoreCreateMutex();
        assert(m_Lock);

        // Subscribe event handlers to their event
        SubscribeToEvent(this, OnSoilSensorCalibrationRequested, MAIN_EVENTS, static_cast<int32_t>(MainEvents::SensorCalibrationRequested));
        SubscribeToEvent(this, OnSoilSensorDataShared, MAIN_EVENTS, static_cast<int32_t>(MainEvents::SensorOutputShared));
    }

    void DataProcessTask::Execute()
    {
        if (IsBitSet(static_cast<uint32_t>(DataProcessBits::Calibration)))
        {
            StartCalibration();
        }
    
        if (IsBitSet(static_cast<uint32_t>(DataProcessBits::DataShared)))
        {
            BroadcastAverageSensorValue();
        }
    }

    // Reset queue and broadcast event with calibration session
    void DataProcessTask::StartCalibration()
    {
        m_DataQueue.Reset();
        EventBus::Get().PostEvent<SampleSession>(m_CalibrationSession, MAIN_EVENTS, static_cast<int32_t>(MainEvents::SensorDataRequested));
    }

    // Post the average soil sensor value through the event bus when a value has become available
    void DataProcessTask::BroadcastAverageSensorValue()
    {
        std::optional<float> averageSensorValue{CalculateAverageSensorValue()};
        if (averageSensorValue.has_value())
        {
            m_AverageSensorValue = averageSensorValue.value();
            EventBus::Get().PostEvent<float>(m_AverageSensorValue, MAIN_EVENTS, static_cast<int32_t>(MainEvents::AverageSensorOutputShared));
        }
    }

    void DataProcessTask::HandleDataShared(float sensorData)
    {
        // Lock semaphore for max amount of wait time
        xSemaphoreTake(m_Lock, s_MaxBlockTime);

        // Add data to the queue
        m_DataQueue.Push(sensorData);

        // Flag to signal a change to queue

        // Release semaphore
        xSemaphoreGive(m_Lock);

        Unblock(static_cast<uint32_t>(DataProcessBits::DataShared));
    }

    // Calculate the average soil sensor value when buffer is full
    std::optional<float> DataProcessTask::CalculateAverageSensorValue() const
    {
        // Only calculate average if the buffer is full
        if (!m_DataQueue.IsFull())
        {
            return std::nullopt;
        }

        // Get sum of all data in buffer
        float dataSum{};
        for (size_t idx{}; idx < s_DataQueueSize; ++idx)
        {
            std::optional<float> value = m_DataQueue.ViewAtIndex(idx);
            if (value.has_value())
            {
                dataSum += value.value();
            }
        }

        return dataSum / m_DataQueue.SizeUsed();
    }

    void DataProcessTask::OnSoilSensorCalibrationRequested(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
    {
        // Get data process task instance
        DataProcessTask* self{static_cast<DataProcessTask*>(eventHandlerArg)};

        // Unblock task to start calibration
        self->Unblock(static_cast<uint32_t>(DataProcessBits::Calibration));
    }

    void DataProcessTask::OnSoilSensorDataShared(void* eventHandlerArg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
    {
        // Get data process task instance
        DataProcessTask* self{static_cast<DataProcessTask*>(eventHandlerArg)};

        // Interpret data as float and add to queue
        float data{*reinterpret_cast<float*>(eventData)};
        self->HandleDataShared(data);

        ESP_LOGI(TAG, "Raw sensor data: %.2f", data);
    }
}