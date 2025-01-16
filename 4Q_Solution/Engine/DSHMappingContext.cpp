#include "pch.h"
#include "DSHMappingContext.h"

Engine::DSHInput::MappingContext::MappingContext() :
	_mappingContext(nullptr)
{
}

void Engine::DSHInput::MappingContext::Setup(DSH::Input::IMappingContext* mappingContext)
{
	mappingContext->AddRef();
	_mappingContext = mappingContext;
}

void Engine::DSHInput::MappingContext::Initialize()
{
}

void Engine::DSHInput::MappingContext::Update(const float deltaTime)
{
	_mappingContext->Update(deltaTime);
}

void Engine::DSHInput::MappingContext::Reset()
{
	_mappingContext->Reset();
}

void Engine::DSHInput::MappingContext::Finalize()
{
	_actions.clear();
	Utility::SafeRelease()(&_mappingContext, "Mapping context is still being referenced.");
}

Engine::Input::IAction* Engine::DSHInput::MappingContext::GetAction(const wchar_t* name)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (name == nullptr) thrower(E_INVALIDARG);
	if (_actions.contains(name)) return &_actions[name];
	DSH::Input::IAction* action = nullptr;
	thrower(_mappingContext->GetAction(name, &action));
	_actions[name].Setup(action);
	Utility::SafeRelease()(&action);
	return &_actions[name];
}
