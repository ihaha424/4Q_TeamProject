#include "pch.h"
#include "Text.h"
#include "GEGraphicsManager.h"

Engine::Component::Text::Text()
	: _geTextRenderer(nullptr)
{
}

void Engine::Component::Text::SetFontPath(const std::filesystem::path& fontPath)
{
	_fontPath = fontPath;
}

void Engine::Component::Text::Initialize(const Modules& modules)
{
	GraphicsComponent::Initialize(modules);
	auto textSystem = _graphicsManager->GetTextSystem();
	textSystem->CreateTextRenderer(&_geTextRenderer);
	
	_geTextRenderer->SetFont(_fontPath.c_str());
}

void Engine::Component::Text::Attach()
{
	auto textSystem = _graphicsManager->GetTextSystem();
	textSystem->RegisterRenderQueue(_geTextRenderer);
}

void Engine::Component::Text::Detach()
{
	auto textSystem = _graphicsManager->GetTextSystem();
	textSystem->UnRegisterRenderQueue(_geTextRenderer);
}

void Engine::Component::Text::Finalize()
{
	_geTextRenderer->Release();
}

void Engine::Component::Text::SetFont(const wchar_t* font) const
{
	_geTextRenderer->SetFont(font);
}

void Engine::Component::Text::SetFontScale(const float x, const float y) const
{
	_geTextRenderer->SetFontScale(x, y);
}

void Engine::Component::Text::SetFontColor(const float r, const float g, const float b, const float a) const
{
	_geTextRenderer->SetFontColor(r, g, b, a);
}

void Engine::Component::Text::SetLayerDepth(const float depth) const
{
	_geTextRenderer->SetLayerDepth(depth);
}

void Engine::Component::Text::SetPivot(const float x, const float y) const
{
	_geTextRenderer->SetPivot(x, y);
}

void Engine::Component::Text::SetRotationFromDegree(const float degree) const
{
	_geTextRenderer->SetRotationFromDegree(degree);
}

void Engine::Component::Text::SetPosition(const float x, const float y, const float z) const
{
	_geTextRenderer->SetPosition(x, y, z);
}

void Engine::Component::Text::SetText(const wchar_t* text) const
{
	_geTextRenderer->SetText(text);
}
