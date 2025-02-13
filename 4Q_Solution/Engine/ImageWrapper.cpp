#include "pch.h"
#include "ImageWrapper.h"

Engine::UI::Wrapper::Image::Image(Math::Rect* rect, const std::filesystem::path& path) :
	Wrapper(rect), _path(path), _matrix(Math::Matrix::Identity)
{
}

void Engine::UI::Wrapper::Image::Initialize(const Modules& modules)
{
	_sprite.SetFilePath(_path);
	_sprite.SetMatrix(&_matrix);
	_sprite.Initialize(modules);
	Wrapper::Initialize(modules);
}

void Engine::UI::Wrapper::Image::Attach()
{
	_sprite.Attach();
	Wrapper::Attach();
}

void Engine::UI::Wrapper::Image::Update(const float deltaGameTime)
{
	_sprite.Update(deltaGameTime);
	Wrapper::Update(deltaGameTime);
}

void Engine::UI::Wrapper::Image::FixedUpdate()
{
	_sprite.FixedUpdate();
	Wrapper::FixedUpdate();
}

void Engine::UI::Wrapper::Image::Detach()
{
	_sprite.Detach();
	Wrapper::Detach();
}

void Engine::UI::Wrapper::Image::Finalize()
{
	_sprite.Finalize();
	Wrapper::Finalize();
}
