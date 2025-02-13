#include "pch.h"
#include "UserInterface.h"

Engine::UI::UserInterface::UserInterface(Math::Rect* rect):
	_padding(),
	_margin(),
	_parentRect(rect),
	_myRect(*rect),
	_childRect(*rect)
{
}

void Engine::UI::UserInterface::Initialize(const Modules& modules)
{
}

void Engine::UI::UserInterface::Attach()
{
}

void Engine::UI::UserInterface::Update(float deltaGameTime)
{
	UpdateRect();
}

void Engine::UI::UserInterface::FixedUpdate()
{
}

void Engine::UI::UserInterface::Detach()
{
}

void Engine::UI::UserInterface::Finalize()
{
}

void Engine::UI::UserInterface::SetPadding(const Math::Padding& padding)
{
	_padding = padding;
}

void Engine::UI::UserInterface::SetMargin(const Math::Margin& margin)
{
	_margin = margin;
}

void Engine::UI::UserInterface::UpdateRect()
{
	UpdateMyRect();
	UpdateChildRect();
}

void Engine::UI::UserInterface::UpdateMyRect()
{
	_myRect = Math::Rect{
		_parentRect->x + _margin.left,
		_parentRect->y + _margin.top,
		_parentRect->width - (_margin.left + _margin.right),
		_parentRect->height - (_margin.top + _margin.bottom)
	};
}

void Engine::UI::UserInterface::UpdateChildRect()
{
	_childRect = Math::Rect{
		_myRect.x + _padding.left,
		_myRect.y + _padding.top,
		_myRect.width - (_padding.left + _padding.right),
		_myRect.height - (_padding.top + _padding.bottom)
	};
}