#include "pch.h"
#include "Application.h"

GameClient::Application::Application(const HINSTANCE instanceHandle) : Engine::Application(instanceHandle)
{
}

void GameClient::Application::DeclareInputActions(Engine::Input::IManager* inputManager)
{
}

void GameClient::Application::PrepareInitialWorld(Engine::Content::Factory::World* worldFactory)
{
}
