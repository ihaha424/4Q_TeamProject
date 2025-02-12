#include "pch.h"
#include "ImageWrapper.h"

Engine::UI::Wrapper::Image::Image(Math::Rect* rect, const std::filesystem::path& path) :
	Wrapper(rect), _path(path)
{
}

void Engine::UI::Wrapper::Image::Initialize(const Modules& modules)
{
	Wrapper::Initialize(modules);
	_sprite.SetFilePath(_path);
	_sprite.Initialize(modules);
}

void Engine::UI::Wrapper::Image::Attach()
{
	Wrapper::Attach();
	_sprite.Attach();
}

void Engine::UI::Wrapper::Image::Update(const float deltaGameTime)
{
	Wrapper::Update(deltaGameTime);
	_sprite.Update(deltaGameTime);
}

void Engine::UI::Wrapper::Image::FixedUpdate()
{
	Wrapper::FixedUpdate();
	_sprite.FixedUpdate();
}

void Engine::UI::Wrapper::Image::Detach()
{
	Wrapper::Detach();
	_sprite.Detach();
}

void Engine::UI::Wrapper::Image::Finalize()
{
	Wrapper::Finalize();
	_sprite.Finalize();
}
