#include "pch.h"
#include "OverlayPanel.h"

Engine::UI::Panel::Overlay::Overlay(Math::Rect* rect) :
	UserInterface(rect)
{
}

Engine::UI::Panel::Overlay::~Overlay()
{
	std::ranges::for_each(_children, Utility::SafeDelete());
	_children.clear();
}

void Engine::UI::Panel::Overlay::Initialize(const Modules& modules)
{
	UserInterface::Initialize(modules);
	std::ranges::for_each(_children, [&modules](const Child* child) { child->Initialize(modules); });
}

void Engine::UI::Panel::Overlay::Attach()
{
	UserInterface::Attach();
	std::ranges::for_each(_children, [](const Child* child) { child->Attach(); });
}

void Engine::UI::Panel::Overlay::Update(float deltaGameTime)
{
	UserInterface::Update(deltaGameTime);
	std::ranges::for_each(_children, [deltaGameTime](const Child* child) { child->Update(deltaGameTime); });
}

void Engine::UI::Panel::Overlay::FixedUpdate()
{
	UserInterface::FixedUpdate();
	std::ranges::for_each(_children, [](const Child* child) { child->FixedUpdate(); });
}

void Engine::UI::Panel::Overlay::Detach()
{
	UserInterface::Detach();
	std::ranges::for_each(_children, [](const Child* child) { child->Detach(); });
}

void Engine::UI::Panel::Overlay::Finalize()
{
	UserInterface::Finalize();
	std::ranges::for_each(_children, [](const Child* child) { child->Finalize(); });
}

void Engine::UI::Panel::Overlay::AddChild(Child* child)
{
	_children.push_back(child);
}

Engine::UI::Panel::Overlay::Child::Child(UserInterface* child) :
	_child(child)
{
}

void Engine::UI::Panel::Overlay::Child::Initialize(const Modules& modules) const
{
	_child->Initialize(modules);
}

void Engine::UI::Panel::Overlay::Child::Attach() const
{
	_child->Attach();
}

void Engine::UI::Panel::Overlay::Child::Update(const float deltaGameTime) const
{
	_child->Update(deltaGameTime);
}

void Engine::UI::Panel::Overlay::Child::FixedUpdate() const
{
	_child->FixedUpdate();
}

void Engine::UI::Panel::Overlay::Child::Detach() const
{
	_child->Detach();
}

void Engine::UI::Panel::Overlay::Child::Finalize() const
{
	_child->Finalize();
}
