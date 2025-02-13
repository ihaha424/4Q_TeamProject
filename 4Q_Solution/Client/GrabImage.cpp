#include "pch.h"
#include "GrabImage.h"

GrabImage::GrabImage(Engine::Math::Rect* rect, const std::filesystem::path& path, float duration):
	FadeImage(rect, path, duration)
{
}

void GrabImage::Initialize(const Engine::Modules& modules)
{
	_matrix = Engine::Math::Matrix::CreateScale(0.2f, 0.2f, 1.0f) * Engine::Math::Matrix::CreateTranslation(200.0f, -24.f, 0);
	FadeImage::Initialize(modules);
}
