#include "pch.h"
#include "AnchorPanel.h"

Engine::UI::Panel::Anchor::Anchor(Math::Rect* rect) :
	UserInterface(rect)
{
}

Engine::UI::Panel::Anchor::~Anchor()
{
	std::ranges::for_each(_children, Utility::SafeDelete());
	_children.clear();
}

void Engine::UI::Panel::Anchor::Initialize(const Modules& modules)
{
	UserInterface::Initialize(modules);
	std::ranges::for_each(_children, [&modules](const Child* child) { child->Initialize(modules); });
}

void Engine::UI::Panel::Anchor::Attach()
{
	UserInterface::Attach();
	std::ranges::for_each(_children, [](const Child* child) { child->Attach(); });
}

void Engine::UI::Panel::Anchor::Update(const float deltaGameTime)
{
	UserInterface::Update(deltaGameTime);
	std::ranges::for_each(_children, [deltaGameTime](const Child* child) { child->Update(deltaGameTime); });
}

void Engine::UI::Panel::Anchor::FixedUpdate()
{
	UserInterface::FixedUpdate();
	std::ranges::for_each(_children, [](const Child* child) { child->FixedUpdate(); });
}

void Engine::UI::Panel::Anchor::Detach()
{
	UserInterface::Detach();
	std::ranges::for_each(_children, [](const Child* child) { child->Detach(); });
}

void Engine::UI::Panel::Anchor::Finalize()
{
	UserInterface::Finalize();
	std::ranges::for_each(_children, [](const Child* child) { child->Finalize(); });
}

void Engine::UI::Panel::Anchor::AddChild(Child* child)
{
	_children.push_back(child);
}


Engine::UI::Panel::Anchor::Child::Child(UserInterface* child):
	_child(child), _horizontal(HorizontalAnchoring::Left), _vertical(VerticalAnchoring::Top)
{
}

void Engine::UI::Panel::Anchor::Child::Initialize(const Modules& modules) const
{
	_child->Initialize(modules);
}

void Engine::UI::Panel::Anchor::Child::Attach() const
{
	_child->Attach();
}

void Engine::UI::Panel::Anchor::Child::Update(const float deltaGameTime) const
{
	_child->Update(deltaGameTime);
}

void Engine::UI::Panel::Anchor::Child::FixedUpdate() const
{
	_child->FixedUpdate();
}

void Engine::UI::Panel::Anchor::Child::Detach() const
{
	_child->Detach();
}

void Engine::UI::Panel::Anchor::Child::Finalize() const
{
	_child->Finalize();
}

std::pair<Engine::UI::Panel::Anchor::Child::HorizontalAnchoring, Engine::UI::Panel::Anchor::Child::VerticalAnchoring>
Engine::UI::Panel::Anchor::Child::GetAnchoring() const
{
	return { _horizontal, _vertical };
}

void Engine::UI::Panel::Anchor::Child::SetAnchoring(const HorizontalAnchoring horizontal, const VerticalAnchoring vertical)
{
	_horizontal = horizontal;
	_vertical = vertical;
}