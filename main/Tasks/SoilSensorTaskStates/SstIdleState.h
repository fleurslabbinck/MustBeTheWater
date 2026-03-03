#ifndef SOIL_SENSOR_TASK_IDLE_STATE_H
#define SOIL_SENSOR_TASK_IDLE_STATE_H

#include <cstdint>
#include "Tasks/SoilSensorTaskStates/SstBaseState.h"

namespace gg
{
    class SstIdleState final : public SstBaseState
    {
    public:
        explicit SstIdleState(StateMachineTask* stateMachine);
        SstIdleState(const SstIdleState&) = delete;
        SstIdleState(SstIdleState&&) = delete;
        SstIdleState& operator=(const SstIdleState&) = delete;
        SstIdleState& operator=(SstIdleState&&) = delete;

    private:
        static constexpr uint32_t m_PrepareDelay{};

        void Update() override;
    };
}
#endif