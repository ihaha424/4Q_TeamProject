#include "pch.h"
#include "DSHHudManager.h"

Engine::DSHHud::Manager::Manager():
	_canvas(nullptr), _nextCanvas(nullptr)
{
}

void Engine::DSHHud::Manager::Initialize()
{
}

void Engine::DSHHud::Manager::Finalize()
{
}

void Engine::DSHHud::Manager::Contraction(const Modules& modules)
{
	if (_nextCanvas != nullptr)
	{
		_nextCanvas->Initialize(modules);
		_nextCanvas->Attach();
		_canvas = _nextCanvas;
		_nextCanvas = nullptr;
	}
}

void Engine::DSHHud::Manager::Update(const float deltaTime) const
{
	if (_canvas != nullptr) _canvas->Update(deltaTime);
}

void Engine::DSHHud::Manager::FixedUpdate() const
{
	if (_canvas != nullptr) _canvas->FixedUpdate();
}

void Engine::DSHHud::Manager::Relaxation()
{
	if (_nextCanvas != nullptr)
	{
		_canvas->Detach();
		_canvas->Finalize();
		_canvas = nullptr;
	}
}

void Engine::DSHHud::Manager::SetCanvas(Canvas* canvas)
{
	_nextCanvas = canvas;
}

void Engine::DSHHud::Manager::ActionThisCanvas() const
{
	if (_canvas != nullptr) _canvas->Action();
}
