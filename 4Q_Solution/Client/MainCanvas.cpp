#include "pch.h"
#include "MainCanvas.h"

MainCanvas::MainCanvas() :
	Canvas(GameClient::Application::GetSize())
{
	auto [anchorChild, overlay] = _rootPanel.CreateChild<Engine::UI::Wrapper::Image>(L"Assets/UI/UI_Logo.png");
}
