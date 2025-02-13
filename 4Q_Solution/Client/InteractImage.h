#pragma once

class InteractImage : public Engine::UI::Wrapper::FadeImage
{
public:
	InteractImage(Engine::Math::Rect* rect, const std::filesystem::path& path, float duration);

	void Initialize(const Engine::Modules& modules) override;
};
