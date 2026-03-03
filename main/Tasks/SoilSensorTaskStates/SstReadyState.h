#ifndef SOIL_SENSOR_TASK_READY_STATE_H
#define SOIL_SENSOR_TASK_READY_STATE_H

#include "Tasks/SoilSensorTaskStates/SstBaseState.h"

namespace gg
{
    class SstReadyState final : public SstBaseState
    {
    public:
        explicit SstReadyState(StateMachineTask* stateMachine);
        SstReadyState(const SstReadyState&) = delete;
        SstReadyState(SstReadyState&&) = delete;
        SstReadyState& operator=(const SstReadyState&) = delete;
        SstReadyState& operator=(SstReadyState&&) = delete;

    private:
        void Update() override;
    };
}
#endif