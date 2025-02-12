#include "pch.h"
#include "Canvas.h"

Engine::Canvas::Canvas(const Math::Size& viewportSize) :
	_rect(Math::Rect(Math::Point::Zero, viewportSize)),
	_rootPanel(&_rect)
{
}

void Engine::Canvas::Initialize(const Modules& modules)
{
	_rootPanel.Initialize(modules);
}

void Engine::Canvas::Attach()
{
	_rootPanel.Attach();
}

void Engine::Canvas::Update(float deltaGameTime)
{
	_rootPanel.Update(deltaGameTime);
}

void Engine::Canvas::FixedUpdate()
{
	_rootPanel.FixedUpdate();
}

void Engine::Canvas::Detach()
{
	_rootPanel.Detach();
}

void Engine::Canvas::Finalize()
{
	_rootPanel.Finalize();
}

Engine::UI::Panel::Anchor* Engine::Canvas::GetRootPanel()
{
	return &_rootPanel;
}
