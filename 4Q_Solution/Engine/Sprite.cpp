#include "pch.h"
#include "Sprite.h"
#include "GEGraphicsManager.h"

Engine::Component::Sprite::Sprite()
	: _geSpriteRenderer(nullptr)
	, _geMatrix(nullptr)
{
	_geSpriteDescription.activeDraw = true;
	_geSpriteDescription.type = GE::SpriteDescription::D2D;
}

void Engine::Component::Sprite::Attach()
{
	Component::Attach();
	_geSpriteRenderer->SetDesc(&_geSpriteDescription);
	_graphicsManager->GetSpriteSystem()->RegisterRenderQueue(_geSpriteRenderer, _geMatrix);
}

void Engine::Component::Sprite::Detach()
{
	Component::Detach();
	_graphicsManager->GetSpriteSystem()->UnRegisterRenderQueue(_geSpriteRenderer);
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
