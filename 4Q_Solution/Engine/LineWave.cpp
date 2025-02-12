#include "pch.h"
#include "LineWave.h"
#include "GEGraphicsManager.h"

Engine::Component::LineWave::LineWave()
	: _geLineRenderer(nullptr)
	, _source(nullptr)
{
}

void Engine::Component::LineWave::Initialize(const Modules& modules)
{
	GraphicsComponent::Initialize(modules);

	auto unlitSystem = _graphicsManager->GetUnlitSystem();

	GE::UNLIT_RENDERER_DESC desc;
	desc.type = GE::UNLIT_RENDERER_DESC::Type::Line;
	GE::IUnlitRenderer* pComponent = nullptr;
	unlitSystem->CreateUnlitRenderer(&pComponent, &desc);

	_geLineRenderer = dynamic_cast<GE::ILineRenderer*>(pComponent);
	//pComponent->Querry((void**)&_geLineRenderer);
	_geLineRenderer->SetBaseTexture(_baseTexturePath.c_str());
	_geLineRenderer->SetMaskTexture(_masktexturePath.c_str());
	_geLineRenderer->SetGradientTexture(_gradientTexturePath.c_str());
}

void Engine::Component::LineWave::Attach()
{
	Component::Attach();
	auto unlitSystem = _graphicsManager->GetUnlitSystem();
	unlitSystem->RegisterRenderQueue(_geLineRenderer, &_geMatrix);
}

void Engine::Component::LineWave::LateUpdate(float deltaTime)
{
	Component::LateUpdate(deltaTime);

	_geMatrix = Engine::Math::Matrix::CreateTranslation(*_source);
	_geLineRenderer->Update(deltaTime);
}

void Engine::Component::LineWave::Detach()
{
	Component::Detach();
	auto unlitSystem = _graphicsManager->GetUnlitSystem();
	unlitSystem->UnRegisterRenderQueue(_geLineRenderer);
}

void Engine::Component::LineWave::Finalize()
{
	Component::Finalize();
	_geLineRenderer->Release();
}

void Engine::Component::LineWave::SetBaseTexturePath(const std::filesystem::path& filePath)
{
	_baseTexturePath = filePath;
}

void Engine::Component::LineWave::SetMaskTexturePath(const std::filesystem::path& filePath)
{
	_masktexturePath = filePath;
}

void Engine::Component::LineWave::SetGradientTexturePath(const std::filesystem::path& filePath)
{
	_gradientTexturePath = filePath;
}

void Engine::Component::LineWave::SetSourcePosition(const Engine::Math::Vector3* source)
{
	_geLineRenderer->SetSourcePosition((float*)source);
	_source = source;
}

void Engine::Component::LineWave::SetDestinationPosition(const Engine::Math::Vector3* destination)
{
	_geLineRenderer->SetDestinationPosition((float*)destination);
}

void Engine::Component::LineWave::SetSegment(unsigned int segments)
{
	_geLineRenderer->SetSegment(segments);
}

void Engine::Component::LineWave::SetPostEffectLayer(unsigned int layer)
{
	_geLineRenderer->SetPostEffectLayer(layer);
}
