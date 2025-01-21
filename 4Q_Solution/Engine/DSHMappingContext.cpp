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
	std::ranges::for_each(_actions, [](auto& pair) { pair.second.Finalize(); });
	_actions.clear();
	Utility::SafeRelease()(&_mappingContext, "Mapping context is still being referenced.");
}

void Engine::DSHInput::MappingContext::GetAction(const wchar_t* name, Input::IAction** action)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (name == nullptr) thrower(E_INVALIDARG);
	if (action == nullptr) thrower(E_INVALIDARG);
	if (_actions.contains(name)) *action = &_actions[name];
	DSH::Input::IAction* dshAction = nullptr;
	thrower(_mappingContext->GetAction(name, &dshAction));
	_actions[name].Setup(dshAction);
	Utility::SafeRelease()(&dshAction);
	*action = &_actions[name];
}
