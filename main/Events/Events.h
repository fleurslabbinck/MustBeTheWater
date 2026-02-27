#ifndef EVENTS_H
#define EVENTS_H

#include "esp_event.h"

// Declare event bases
ESP_EVENT_DECLARE_BASE(MAIN_EVENTS);

namespace gg
{
    enum class MainEvents : int32_t
    {
        RequestSensorData,
        ShareSensorOutput,
    };
}
#endif