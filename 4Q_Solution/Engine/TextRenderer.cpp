#include "pch.h"
#include "TextRenderer.h"
#include "GEGraphicsManager.h"

Engine::Component::TextRenderer::TextRenderer(std::filesystem::path font)
	: _geTextRenderer(nullptr)
	, _font(std::move(font))
{
}

void Engine::Component::TextRenderer::Initialize()
{
	auto textSystem = _graphicsManager->GetTextSystem();
	textSystem->CreateTextRenderer(&_geTextRenderer);
	
	_geTextRenderer->SetFont(_font.c_str());
}

void Engine::Component::TextRenderer::Attach()
{
	auto textSystem = _graphicsManager->GetTextSystem();
	textSystem->RegisterRenderQueue(_geTextRenderer);
}

void Engine::Component::TextRenderer::Detach()
{
	auto textSystem = _graphicsManager->GetTextSystem();
	textSystem->UnRegisterRenderQueue(_geTextRenderer);
}

void Engine::Component::TextRenderer::Finalize()
{
	_geTextRenderer->Release();
}

void Engine::Component::TextRenderer::SetFont(const wchar_t* font)
{
	_geTextRenderer->SetFont(font);
}

void Engine::Component::TextRenderer::SetFontScale(const float x, const float y)
{
	_geTextRenderer->SetFontScale(x, y);
}

void Engine::Component::TextRenderer::SetFontColor(const float r, const float g, const float b, const float a)
{
	_geTextRenderer->SetFontColor(r, g, b, a);
}

void Engine::Component::TextRenderer::SetLayerDepth(const float depth)
{
	_geTextRenderer->SetLayerDepth(depth);
}

void Engine::Component::TextRenderer::SetPivot(const float x, const float y)
{
	_geTextRenderer->SetPivot(x, y);
}

void Engine::Component::TextRenderer::SetRotationFromDegree(const float degree)
{
	_geTextRenderer->SetRotationFromDegree(degree);
}

void Engine::Component::TextRenderer::SetPosition(const float x, const float y, const float z)
{
	_geTextRenderer->SetPosition(x, y, z);
}

void Engine::Component::TextRenderer::SetText(const wchar_t* text)
{
	_geTextRenderer->SetText(text);
}