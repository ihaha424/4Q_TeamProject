#include "pch.h"
#include "FiniteStateMachine.h"
#include "State.h"

Engine::Component::FiniteStateMachine::FiniteStateMachine()
	: _currStateIndex(0)
	, _prevStateIndex(0)
{
}

void Engine::Component::FiniteStateMachine::Update(float deltaTime)
{
	int nextState = _states[_currStateIndex]->Update(deltaTime);

	if (0 < nextState)
	{
		_states[_currStateIndex]->OnExit();
		_currStateIndex = nextState;
		_states[_currStateIndex]->OnStart();
	}
}

void Engine::Component::FiniteStateMachine::Finalize()
{
	constexpr Utility::SafeDelete deletor;
	std::ranges::for_each(_states, deletor);
}

void Engine::Component::FiniteStateMachine::Reset()
{
	for (auto& state : _states)
	{
		if (nullptr != state)
			state->Reset();
	}
}

void Engine::Component::FiniteStateMachine::Reset(unsigned int group)
{
	_states[group]->Reset();
}

void Engine::Component::FiniteStateMachine::SetMaxState(unsigned int maxStates)
{
	_states.resize(maxStates);
}

void Engine::Component::FiniteStateMachine::AddState(unsigned int group, State* pState)
{
	if (nullptr == pState)
		return;

	_states[group] = pState;
}

void Engine::Component::FiniteStateMachine::ChangeState(unsigned int nextState)
{
	if (0 != _currStateIndex) _states[_currStateIndex]->OnExit();
	_currStateIndex = nextState;
	if (0 != _currStateIndex) _states[_currStateIndex]->OnStart();
}