#ifndef STATE_MACHINE_TASK_H
#define STATE_MACHINE_TASK_H

#include <memory>
#include <unordered_map>
#include <type_traits>
#include "Tasks/Core/NotificationTask.h"
#include "State/BaseState.h"

namespace gg
{
    using State = unsigned int;

    class StateMachineTask : public NotificationTask
    {
    public:
        StateMachineTask() = default;
        StateMachineTask(const StateMachineTask&) = delete;
        StateMachineTask(StateMachineTask&&) = delete;
        StateMachineTask& operator=(const StateMachineTask&) = delete;
        StateMachineTask& operator=(StateMachineTask&&) = delete;

        void SwitchState(State newState, uint32_t delay);
        void SwitchState(State newState);
        void SetDelay(uint32_t delay);

    protected:
        // Call before task creation
        virtual void InitializeStateMachine() = 0;

        // Add all states to the unordered map through their state id
        template<typename StateType>
        void AddState(State stateId)
        {
            static_assert(std::is_base_of<BaseState, StateType>::value, "StateType must be a derived class of BaseState");
            std::unique_ptr<BaseState> state{std::make_unique<StateType>(this)};
            m_States[stateId] = std::move(state);
        }

    private:
        State m_CurrentState{};
        std::unordered_map<State, std::unique_ptr<BaseState>> m_States{};

        void Execute() override;
    };
}
#endif