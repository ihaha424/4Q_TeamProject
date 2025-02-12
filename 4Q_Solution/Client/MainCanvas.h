#pragma once

namespace Engine::UI::Wrapper
{
	class FadeImage;
}

class MainCanvas : public Engine::Canvas
{
public:
	MainCanvas();
	explicit MainCanvas(const Engine::Math::Size& viewportSize);

	void FadeIn() const;

	void Action() override;

private:
	Engine::UI::Wrapper::FadeImage* _fadeMask;
};