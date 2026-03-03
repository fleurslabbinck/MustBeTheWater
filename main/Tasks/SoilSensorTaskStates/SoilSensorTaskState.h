#ifndef SOIL_SENSOR_TASK_STATE_H
#define SOIL_SENSOR_TASK_STATE_H

namespace gg
{
    enum class SoilSensorTaskState : uint8_t
    {
        Idle,
        Prepare,
        Ready,
        Reset
    };
}
#endif