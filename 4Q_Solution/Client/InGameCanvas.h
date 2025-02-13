#pragma once

class GrabImage;
class InteractImage;

namespace Engine::UI::Wrapper
{
	class FadeImage;
}

class InGameCanvas final : public Engine::Canvas
{
	enum class Sequence
	{
		MaskFaded,
		MaskFadingOut,
		MoveTutorialFadingIn,
		MoveTutorialFaded,
		MoveTutorialFadingOut,
		ViewTutorialFadingIn,
		ViewTutorialFaded,
		ViewTutorialFadingOut,
		JumpTutorialFadingIn,
		JumpTutorialFaded,
		JumpTutorialFadingOut,
		GamePlaying,
	};
public:
	InGameCanvas();
	explicit InGameCanvas(const Engine::Math::Size& viewportSize);

	void Initialize(const Engine::Modules& modules) override;
	void Attach() override;

	void MoveTutorialDone();
	void ViewTutorialDone();
	void JumpTutorialDone();

	void ShowInteractUI() const;
	void HideInteractUI() const;
	void ShowGrabUI() const;
	void HideGrabUI() const;

private:
	Sequence _sequence;

	Engine::UI::Wrapper::FadeImage* _fadeMask;
	Engine::UI::Wrapper::FadeImage* _moveTutorial;
	Engine::UI::Wrapper::FadeImage* _viewTutorial;
	Engine::UI::Wrapper::FadeImage* _jumpTutorial;
	InteractImage* _interactImage;
	GrabImage* _grabImage;
};