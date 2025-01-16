#include "pch.h"
#include "RenderSystem.h"

void Engine::Manager::GraphicsSystem::RenderSystem::Initialize(GE::IRenderSystem* renderSystem, const GE::RENDERER_DESC* desc)
{
	assert(renderSystem != nullptr);
	assert(_renderSystem == nullptr);
	_renderSystem = renderSystem;
	_renderSystem->Initialize(desc);
	_renderSystem->GetTextSystem(&_textSystem);
}

void Engine::Manager::GraphicsSystem::RenderSystem::Render() const
{
	assert(_renderSystem != nullptr);
	_renderSystem->Render();
}

void Engine::Manager::GraphicsSystem::RenderSystem::Finalize()
{
	Utility::SafeRelease()(&_renderSystem);
}

void Engine::Manager::GraphicsSystem::RenderSystem::CreateMatrix(GE::IMatrix** matrix) const
{
	assert(_renderSystem != nullptr);
	_renderSystem->CreateMatrix(matrix);
}

void Engine::Manager::GraphicsSystem::RenderSystem::CreateMeshRenderer(GE::IMeshRenderer** component,
	const GE::MESH_RENDERER_DESC* desc) const
{
	assert(_renderSystem != nullptr);
	_renderSystem->CreateMeshRenderer(component, desc);
}

void Engine::Manager::GraphicsSystem::RenderSystem::RegisterRenderQueue(GE::IMeshRenderer* component,
	GE::IMatrix* matrix) const
{
	assert(_renderSystem != nullptr);
	_renderSystem->RegisterRenderQueue(component, matrix);
}

void Engine::Manager::GraphicsSystem::RenderSystem::UnRegisterRenderQueue(GE::IMeshRenderer* component) const
{
	assert(_renderSystem != nullptr);
	_renderSystem->UnRegisterRenderQueue(component);
}

void Engine::Manager::GraphicsSystem::RenderSystem::RegisterFont(const wchar_t* name, const wchar_t* filePath) const
{
	assert(_textSystem != nullptr);
	_textSystem->RegisterFont(name, filePath);
}

void Engine::Manager::GraphicsSystem::RenderSystem::CreateTextRenderer(GE::ITextRenderer** textRenderer) const
{
	assert(_textSystem != nullptr);
	_textSystem->CreateTextRenderer(textRenderer);
}

void Engine::Manager::GraphicsSystem::RenderSystem::RegisterRenderQueue(GE::ITextRenderer* textRenderer) const
{
	assert(_textSystem != nullptr);
	_textSystem->RegisterRenderQueue(textRenderer);
}

void Engine::Manager::GraphicsSystem::RenderSystem::UnRegisterRenderQueue(GE::ITextRenderer* textRenderer) const
{
	assert(_textSystem != nullptr);
	_textSystem->UnRegisterRenderQueue(textRenderer);
}


