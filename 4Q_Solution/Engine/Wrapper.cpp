#include "pch.h"
#include "Wrapper.h"

Engine::UI::Wrapper::Wrapper::Wrapper(Math::Rect* rect) :
	UserInterface(rect), _child(nullptr)
{
}

Engine::UI::Wrapper::Wrapper::~Wrapper()
{
	Utility::SafeDelete()(&_child);
}

void Engine::UI::Wrapper::Wrapper::Initialize(const Modules& modules)
{
	UserInterface::Initialize(modules);
	if (_child != nullptr) _child->Initialize(modules);
}

void Engine::UI::Wrapper::Wrapper::Attach()
{
	UserInterface::Attach();
	if (_child != nullptr) _child->Attach();
}

void Engine::UI::Wrapper::Wrapper::Update(const float deltaGameTime)
{
	UserInterface::Update(deltaGameTime);
	if (_child != nullptr) _child->Update(deltaGameTime);
}

void Engine::UI::Wrapper::Wrapper::FixedUpdate()
{
	UserInterface::FixedUpdate();
	if (_child != nullptr) _child->FixedUpdate();
}

void Engine::UI::Wrapper::Wrapper::Detach()
{
	UserInterface::Detach();
	if (_child != nullptr) _child->Detach();
}

void Engine::UI::Wrapper::Wrapper::Finalize()
{
	UserInterface::Finalize();
	if (_child != nullptr) _child->Finalize();
}

void Engine::UI::Wrapper::Wrapper::SetChild(UserInterface* child)
{
	Utility::SafeDelete()(&_child);
	_child = child;
}
