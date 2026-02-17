#ifndef SOIL_SENSOR_TASK_BASE_STATE_H
#define SOIL_SENSOR_TASK_BASE_STATE_H

#include "State/BaseState.h"

namespace gg
{
    class SoilSensorTask;
    class SstBaseState : public BaseState
    {
    public:
        explicit SstBaseState(StateMachineTask* stateMachine);
        SstBaseState(const SstBaseState&) = delete;
        SstBaseState(SstBaseState&&) = delete;
        SstBaseState& operator=(const SstBaseState&) = delete;
        SstBaseState& operator=(SstBaseState&&) = delete;

    protected:
        SoilSensorTask* m_SoilSensorTask{nullptr};
    };
}
#endif