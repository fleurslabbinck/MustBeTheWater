#ifndef BASE_STATE_H
#define BASE_STATE_H

namespace gg
{
    class StateMachineTask;

    class BaseState
    {
    public:
        explicit BaseState(StateMachineTask* stateMachine)
            : m_StateMachine{stateMachine}
        {}

        ~BaseState() = default;
        BaseState(const BaseState&) = delete;
        BaseState(BaseState&&) = delete;
        BaseState& operator=(const BaseState&) = delete;
        BaseState& operator=(BaseState&&) = delete;

        virtual void Update() = 0;

    protected:
        StateMachineTask* GetStateMachine() const {return m_StateMachine;}

    private:
        StateMachineTask* m_StateMachine{nullptr};
    };
}
#endif