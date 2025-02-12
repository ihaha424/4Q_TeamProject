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
	auto startImage = logoImage->CreateChild<Engine::UI::Wrapper::Image>(L"Assets/UI/UI_GameStart_Off.png");
	startImage->CreateChild<Engine::UI::Wrapper::BlinkImage>(L"Assets/UI/UI_GameStart_On.png", 1.0f);
}
