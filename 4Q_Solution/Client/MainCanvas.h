#pragma once

namespace Engine::UI::Wrapper
{
	class FadeImage;
}

class MainCanvas : public Engine::Canvas
{
	enum class Sequence
	{
		MaskNotFaded,
		MaskFadingIn,
	};
public:
	MainCanvas();
	explicit MainCanvas(const Engine::Math::Size& viewportSize);

	void FadeIn();

	void Action() override;

	void BindOnFadeIn(const Engine::UI::Wrapper::FadeImage::Event& event) const;

private:
	Sequence _sequence;

	Engine::UI::Wrapper::FadeImage* _fadeMask;
};