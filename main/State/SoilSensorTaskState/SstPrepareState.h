#ifndef SOIL_SENSOR_TASK_PREPARE_STATE_H
#define SOIL_SENSOR_TASK_PREPARE_STATE_H

#include "State/SoilSensorTaskState/SstBaseState.h"

namespace gg
{
    class SstPrepareState final : public SstBaseState
    {
    public:
        explicit SstPrepareState(StateMachineTask* owner);
        SstPrepareState(const SstPrepareState&) = delete;
        SstPrepareState(SstPrepareState&&) = delete;
        SstPrepareState& operator=(const SstPrepareState&) = delete;
        SstPrepareState& operator=(SstPrepareState&&) = delete;

    private:
        void Update() override;
    };
}
#endif