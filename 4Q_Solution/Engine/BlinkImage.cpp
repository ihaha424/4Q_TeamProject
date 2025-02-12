#include "pch.h"
#include "BlinkImage.h"

Engine::UI::Wrapper::BlinkImage::BlinkImage(Math::Rect* rect, const std::filesystem::path& path, float blinkTime)
	: FadeImage(rect, path, blinkTime)
{
}

void Engine::UI::Wrapper::BlinkImage::Initialize(const Modules& modules)
{
	BindOnFadeInEnd([this]() {FadeOut(); });
	BindOnFadeOutEnd([this]() {FadeIn(); });
	FadeImage::Initialize(modules);

	FadeIn();
}
