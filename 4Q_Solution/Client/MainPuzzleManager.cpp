#include "pch.h"
#include "MainPuzzleManager.h"

void MainPuzzleManager::PreInitialize(const Engine::Modules& modules)
{
	PuzzleManager::PreInitialize(modules);
	_sync->SetSerialNumber(9000);
	myManager = modules.gameStateManager;
}

void MainPuzzleManager::PostInitialize(const Engine::Modules& modules)
{
	Engine::Object::PostInitialize(modules);
	myManager->Subscribe(L"GameCoreData", [this](const std::wstring& name, const std::any& value)
		{
			DataChangeCallBack(name, value);
		}
	, this);
}

void MainPuzzleManager::SetStart(const PlayMsg::PuzzleStart* msg)
{
}

void MainPuzzleManager::SetFinish(const PlayMsg::PuzzleStart* msg)
{
}

void MainPuzzleManager::SetInteract(const PlayMsg::InteractObject* msg)
{
}

void MainPuzzleManager::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
