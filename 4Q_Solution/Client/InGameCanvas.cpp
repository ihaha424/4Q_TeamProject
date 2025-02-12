#include "pch.h"
#include "InGameCanvas.h"

#include "DelayCall.h"
#include "../Engine/OverlayPanel.h"

InGameCanvas::InGameCanvas():
	InGameCanvas(GameClient::Application::GetSize())
{
}

InGameCanvas::InGameCanvas(const Engine::Math::Size& viewportSize):
	Canvas(viewportSize), _sequence(Sequence::MaskFaded)
{
	auto [anchorChild, overlay] = _rootPanel.CreateChild<Engine::UI::Panel::Overlay>();

	auto [moveTutorialOverlayChild, moveTutorial] = overlay->CreateChild<Engine::UI::Wrapper::FadeImage>(L"Assets/UI/UI_Gamepad_Lstick.png", 0.5f);
	_moveTutorial = moveTutorial;

	auto [viewTutorialOverlayChild, viewTutorial] = overlay->CreateChild<Engine::UI::Wrapper::FadeImage>(L"Assets/UI/UI_Gamepad_Rstick.png", 0.5f);
	_viewTutorial = viewTutorial;

	auto [jumpTutorialOverlayChild, jumpTutorial] = overlay->CreateChild<Engine::UI::Wrapper::FadeImage>(L"Assets/UI/UI_Gamepad_A.png", 0.5f);
	_jumpTutorial = jumpTutorial;

	auto [fadeMaskOverlayChild, fadeMask] = overlay->CreateChild<Engine::UI::Wrapper::FadeImage>(L"Assets/UI/UI_Fade_Mask.png", 1.0f);
	_fadeMask = fadeMask;
}

void InGameCanvas::Initialize(const Engine::Modules& modules)
{
	Canvas::Initialize(modules);
	_fadeMask->SetOpacity(1.0f);
	_fadeMask->BindOnFadeOutEnd([this]()
		{
		AsyncDelayCall()
			_moveTutorial->FadeIn(1.5f);
			_sequence = Sequence::MoveTutorialFadingIn;
		});

	_moveTutorial->SetOpacity(0.0f);
	_moveTutorial->BindOnFadeInEnd([this]()
		{
			_sequence = Sequence::MoveTutorialFaded;
		});
	_moveTutorial->BindOnFadeOutEnd([this]()
		{
			_viewTutorial->FadeIn(1.5f);
			_sequence = Sequence::ViewTutorialFadingIn;
		});

	_viewTutorial->SetOpacity(0.0f);
	_viewTutorial->BindOnFadeInEnd([this]()
		{
			_sequence = Sequence::ViewTutorialFaded;
		});


}

void InGameCanvas::Attach()
{
	Canvas::Attach();
	_fadeMask->FadeOut();
	_sequence = Sequence::MaskFadingOut;
}

void InGameCanvas::MoveTutorialDone()
{
	if (_sequence != Sequence::MoveTutorialFaded) return;
	_moveTutorial->FadeOut(0.5f);
	_sequence = Sequence::MoveTutorialFadingOut;
}

void InGameCanvas::ViewTutorialDone()
{
	if (_sequence != Sequence::ViewTutorialFaded) return;
	_viewTutorial->FadeOut(0.5f);
	_sequence = Sequence::ViewTutorialFadingOut;
}
