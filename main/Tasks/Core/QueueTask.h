#ifndef QUEUE_TASK_H
#define QUEUE_TASK_H

#include "Tasks/Core/Task.h"

extern "C" {
    #include "freertos/queue.h"
}

namespace gg
{
    template<class ItemType>
    class QueueTask : public Task
    {
    public:
        QueueTask(uint32_t queueLength)
        {
            m_Queue = xQueueCreate(queueLength, sizeof(ItemType));
        }

        ~QueueTask()
        {
            if (m_Queue)
            {
                vQueueDelete(m_Queue);
                m_Queue = nullptr;
            }
        }

        QueueTask(const QueueTask&) = delete;
        QueueTask(QueueTask&&) = delete;
        QueueTask& operator=(const QueueTask&) = delete;
        QueueTask& operator=(QueueTask&&) = delete;

        bool Enqueue(const ItemType& item)
        {
            return m_Queue && xQueueSend(m_Queue, &item, 0) == pdPASS;
        }

    protected:
        ItemType m_Buffer{};
        
    private:
        QueueHandle_t m_Queue{nullptr};

        bool WaitForWork() override
        {
            if (m_Queue)
            {
                // Task is blocked until an item is added to the queue
                xQueueReceive(m_Queue, &m_Buffer, portMAX_DELAY);
            }

            // Ignore potential received data if shutting down
            return !StopRequested();
        }

        void Unblock() override
        {
            // Add empty item to the queue to wake up the task
            m_Buffer = ItemType();
            xQueueSend(m_Queue, &m_Buffer, 0);
        }
    };
}
#endif