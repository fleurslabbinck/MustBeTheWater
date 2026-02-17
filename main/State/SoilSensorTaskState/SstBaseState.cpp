#include "SstBaseState.h"

#include "Tasks/SoilSensorTask.h"

namespace gg
{
    SstBaseState::SstBaseState(StateMachineTask* stateMachine)
        : BaseState(stateMachine), m_SoilSensorTask{static_cast<SoilSensorTask*>(GetStateMachine())}
    {}
}