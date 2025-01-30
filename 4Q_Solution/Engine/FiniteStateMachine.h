#pragma once

namespace Engine::Component
{
    class FiniteStateMachine : public Component
    {
    public:
        FiniteStateMachine();

    public:
        void Update(float deltaTime) override;
        void Finalize() override;

    public:
        State* GetCurrState(unsigned int state) { return _states[state]; }
        unsigned int GetCurrState() const { return _currStateIndex; }

        void SetMaxState(unsigned int maxStates);
        void AddState(unsigned int group, State* pState);
        void ChangeState(unsigned int nextState);
        void Reset();
        void Reset(unsigned int group);

    private:
        std::vector<State*> _states;
        unsigned int        _currStateIndex;
        unsigned int        _prevStateIndex;
    };
}