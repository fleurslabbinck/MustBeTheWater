#ifndef SENDER_H
#define SENDER_H

#include "esp_event.h"

#include "Helpers/TaskConfig.h"

namespace gg
{
    class Sender
    {
    public:
        Sender() = default;
        ~Sender();
        Sender(const Sender&) = delete;
        Sender(Sender&&) = delete;
        Sender& operator=(const Sender&) = delete;
        Sender& operator=(Sender&&) = delete;

        void PinEventLoopToCore(CoreSelect core);

        esp_event_loop_handle_t GetEventLoopHandle() const {return m_EventLoopHandle;}

    protected:
        void CreateEventLoop(const TaskConfig& taskConfig, int32_t queueSize);

        // Ensure data will still exist when accessed be listener
        template<typename DataType>
        void SendEvent(const DataType& eventData, esp_event_base_t eventBase, int32_t eventId)
        {
            ESP_ERROR_CHECK(esp_event_post_to(
                m_EventLoopHandle,
                eventBase,
                eventId,
                &eventData,
                sizeof(eventData),
                portMAX_DELAY
            ));
        }

    private:
        BaseType_t m_Core{tskNO_AFFINITY};
        esp_event_loop_handle_t m_EventLoopHandle{nullptr};
    };
}
#endif