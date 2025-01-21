#include "pch.h"
#include "DSHDown.h"
#include "DSHNegative.h"
#include "DSHSwizzleAxis.h"
#include "DSHInputButtonComponent.h"
#include "DSHInputAxisComponent.h"

Engine::DSHInput::Trigger::Down::Down() :
	_down(nullptr)
{
}

void Engine::DSHInput::Trigger::Down::Setup(DSH::Input::Trigger::IDown* down)
{
	down->AddRef();
	_down = down;
}

void Engine::DSHInput::Trigger::Down::Finalize()
{
	Utility::SafeRelease()(&_down);
}

void Engine::DSHInput::Trigger::Down::SetComponent(Input::Component::IButtonComponent* component)
{
	const Component::ButtonComponent* buttonComponent = static_cast<Component::ButtonComponent*>(component);
	_down->SetComponent(buttonComponent->Get());
}

void Engine::DSHInput::Trigger::Down::SetComponent(Input::Component::IAxisComponent* component)
{
	const Component::AxisComponent* axisComponent = static_cast<Component::AxisComponent*>(component);
	_down->SetComponent(axisComponent->Get());
}

void Engine::DSHInput::Trigger::Down::AddModifier(Input::Modifier::INegative* modifier)
{
	const Modifier::Negative* negative = static_cast<Modifier::Negative*>(modifier);
	_down->AddModifier(negative->Get());
}

void Engine::DSHInput::Trigger::Down::AddModifier(Input::Modifier::ISwizzleAxis* modifier)
{
	const Modifier::SwizzleAxis* swizzleAxis = static_cast<Modifier::SwizzleAxis*>(modifier);
	_down->AddModifier(swizzleAxis->Get());
}