#include "pch.h"
#include "Sprite.h"
#include "GEGraphicsManager.h"

Engine::Component::Sprite::Sprite()
	: _geSpriteRenderer(nullptr)
	, _geMatrix(nullptr)
	, _width(0.f), _height(0.f)
{
	_geSpriteDescription.activeDraw = true;
	_geSpriteDescription.alpha = 1.f;
	_geSpriteDescription.type = GE::SpriteDescription::D2D;
}

void Engine::Component::Sprite::Initialize(const Modules& modules)
{
	GraphicsComponent::Initialize(modules);

	auto spriteSystem = _graphicsManager->GetSpriteSystem();
	spriteSystem->CreateTextRenderer(&_geSpriteRenderer, _filePath.c_str());
	_geSpriteRenderer->GetImageSize(&_width, &_height);
}

void Engine::Component::Sprite::Attach()
{
	Component::Attach();
	_geSpriteRenderer->SetDesc(&_geSpriteDescription);	
	auto spriteSystem = _graphicsManager->GetSpriteSystem();
	spriteSystem->RegisterRenderQueue(_geSpriteRenderer, &_geWorld);
}

void Engine::Component::Sprite::Update(float deltaTime)
{
	_geWorld = Engine::Math::Matrix::CreateScale(_width, _height, 1.f) * (*_geMatrix);
}

void Engine::Component::Sprite::Detach()
{
	Component::Detach();
	auto spriteSystem = _graphicsManager->GetSpriteSystem();
	spriteSystem->UnRegisterRenderQueue(_geSpriteRenderer);
}

void Engine::Component::Sprite::Finalize()
{
	_geSpriteRenderer->Release();
}

void Engine::Component::Sprite::SetMatrix(Math::Matrix* matrix)
{
	_geMatrix = matrix;
}

void Engine::Component::Sprite::SetFilePath(const std::filesystem::path& filePath)
{
	_filePath = filePath;
}

void Engine::Component::Sprite::SetActiveDraw(bool isActive)
{
	_geSpriteDescription.activeDraw = isActive;
	_geSpriteRenderer->SetDesc(&_geSpriteDescription);
}

void Engine::Component::Sprite::SetAlpha(float alpha)
{
	_geSpriteDescription.alpha = alpha;
	_geSpriteRenderer->SetDesc(&_geSpriteDescription);
}
