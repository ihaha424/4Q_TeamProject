#include "pch.h"
#include "InGameCanvas.h"

InGameCanvas::InGameCanvas():
	InGameCanvas(GameClient::Application::GetSize())
{
}

InGameCanvas::InGameCanvas(const Engine::Math::Size& viewportSize):
	Canvas(viewportSize)
{
	auto [anchorChild, fadeImage] = _rootPanel.CreateChild<Engine::UI::Wrapper::FadeImage>(L"Assets/UI/UI_Fade_Mask.png", 1.0f);
	_fadeMask = fadeImage;
}

void InGameCanvas::Initialize(const Engine::Modules& modules)
{
	Canvas::Initialize(modules);
	_fadeMask->SetOpacity(1.0f);
}

void InGameCanvas::Attach()
{
	Canvas::Attach();
	_fadeMask->FadeOut();
}
