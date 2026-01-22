#include "pch.h"
#include "InteractImage.h"

InteractImage::InteractImage(Engine::Math::Rect* rect, const std::filesystem::path& path, const float duration) :
	FadeImage(rect, path, duration)
{
}

void InteractImage::Initialize(const Engine::Modules& modules)
{
	_matrix = Engine::Math::Matrix::CreateScale(0.2f, 0.2f, 1.0f) * Engine::Math::Matrix::CreateTranslation(200.0f, 50.f, 0);
	FadeImage::Initialize(modules);
}
