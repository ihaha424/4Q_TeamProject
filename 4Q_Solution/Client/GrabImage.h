#pragma once

class GrabImage : public Engine::UI::Wrapper::FadeImage
{
public:
	GrabImage(Engine::Math::Rect* rect, const std::filesystem::path& path, float duration);

	void Initialize(const Engine::Modules& modules) override;
};
