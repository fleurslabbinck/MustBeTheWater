#ifndef SOIL_SENSOR_TASK_RESET_STATE_H
#define SOIL_SENSOR_TASK_RESET_STATE_H

#include "State/SoilSensorTaskState/SstBaseState.h"

namespace gg
{
    class SstResetState final : public SstBaseState
    {
    public:
        explicit SstResetState(StateMachineTask* stateMachine);
        SstResetState(const SstResetState&) = delete;
        SstResetState(SstResetState&&) = delete;
        SstResetState& operator=(const SstResetState&) = delete;
        SstResetState& operator=(SstResetState&&) = delete;

    private:
        void Update() override;
    };
}
#endif