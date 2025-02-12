#include "pch.h"
#include "MainCanvas.h"

MainCanvas::MainCanvas() :
	MainCanvas(GameClient::Application::GetSize())
{
}

MainCanvas::MainCanvas(const Engine::Math::Size& viewportSize):
	Canvas(viewportSize)
{
	auto [anchorChild, logoImage] = _rootPanel.CreateChild<Engine::UI::Wrapper::Image>(L"Assets/UI/UI_Logo.png");
	const auto startImage = logoImage->CreateChild<Engine::UI::Wrapper::Image>(L"Assets/UI/UI_GameStart_Off.png");
	const auto blinkImage = startImage->CreateChild<Engine::UI::Wrapper::BlinkImage>(L"Assets/UI/UI_GameStart_On.png", 1.0f);
	_fadeMask = blinkImage->CreateChild<Engine::UI::Wrapper::FadeImage>(L"Assets/UI/UI_Fade_Mask.png", 1.0f);
}

void MainCanvas::FadeIn() const
{
	_fadeMask->FadeIn();
}

void MainCanvas::Action()
{
	FadeIn();
}

void MainCanvas::BindOnFadeIn(const Engine::UI::Wrapper::FadeImage::Event& event) const
{
	_fadeMask->BindOnFadeInEnd(event);
}
