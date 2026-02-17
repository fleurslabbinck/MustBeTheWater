#include "StateMachineTask.h"

namespace gg
{
    void StateMachineTask::Execute()
    {
        // Update state behavior
        BaseState* state{m_States[m_CurrentState].get()};
        if (state)
        {
            state->Update();
        }
    }

    // Switch to a new state that will start after given delay
    void StateMachineTask::SwitchState(State newState, uint32_t delay)
    {
        m_CurrentState = newState;
        ChangeWaitTime(delay);
    }

    // Switch to a new state that will start and reset delay
    void StateMachineTask::SwitchState(State newState)
    {
        m_CurrentState = newState;
        ResetWaitTime();
    }
}