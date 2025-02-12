#include "pch.h"
#include "ButtonWrapper.h"

Engine::UI::Wrapper::Button::Button(Math::Rect* rect):
	Wrapper(rect), _isHover(false)
{
}

void Engine::UI::Wrapper::Button::Update(const float deltaTime)
{
	Wrapper::Update(deltaTime);
    HoverCheck();
    ClickCheck();
}

void Engine::UI::Wrapper::Button::BindOnHoverBegin(const Event& event)
{
	_onHoverBegin = event;
}

void Engine::UI::Wrapper::Button::BindOnHoverEnd(const Event& event)
{
	_onHoverEnd = event;
}

void Engine::UI::Wrapper::Button::BindOnClick(const Event& event)
{
	_onClick = event;
}

void Engine::UI::Wrapper::Button::HoverCheck()
{
    Input::Device::IMouse* mouse = nullptr;
    Application::GetInputManager()->GetDevice(&mouse);
    if (const Math::Point mousePosition = mouse->GetPosition(); 
        _myRect.Contains(mousePosition.x, mousePosition.y) && 
        _onHoverBegin &&
        !_isHover)
    {
        _onHoverBegin();
        _isHover = true;
    }
    else if (!_myRect.Contains(mousePosition.x, mousePosition.y) &&
        _onHoverEnd && 
        _isHover)
    {
        _onHoverEnd();
        _isHover = false;
    }
}

void Engine::UI::Wrapper::Button::ClickCheck() const
{
    Input::Device::IMouse* mouse = nullptr;
    Application::GetInputManager()->GetDevice(&mouse);
    if (const Math::Point mousePosition = mouse->GetPosition();
        mouse->IsButtonDown(Input::Device::IMouse::Button::Left) &&
        _myRect.Contains(mousePosition.x, mousePosition.y) && 
        _onClick)
    {
        _onClick();
    }
}
