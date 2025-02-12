#include "pch.h"
#include "TextElement.h"

Engine::UI::Element::Text::Text(Math::Rect* rect):
	UserInterface(rect)
{
}

Engine::UI::Element::Text::Text(Math::Rect* rect, const std::wstring& text):
	UserInterface(rect), _text(text)
{
}

void Engine::UI::Element::Text::SetText(const std::wstring& text)
{
	_text = text;
}
