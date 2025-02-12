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

void Engine::UI::Wrapper::Wrapper::Initialize()
{
	UserInterface::Initialize();
	_child->Initialize();
}

void Engine::UI::Wrapper::Wrapper::Attach()
{
	UserInterface::Attach();
	_child->Attach();
}

void Engine::UI::Wrapper::Wrapper::Update(const float deltaGameTime)
{
	UserInterface::Update(deltaGameTime);
	_child->Update(deltaGameTime);
}

void Engine::UI::Wrapper::Wrapper::FixedUpdate()
{
	UserInterface::FixedUpdate();
	_child->FixedUpdate();
}

void Engine::UI::Wrapper::Wrapper::Detach()
{
	UserInterface::Detach();
	_child->Detach();
}

void Engine::UI::Wrapper::Wrapper::Finalize()
{
	UserInterface::Finalize();
	_child->Finalize();
}

void Engine::UI::Wrapper::Wrapper::SetChild(UserInterface* child)
{
	Utility::SafeDelete()(&_child);
	_child = child;
}
