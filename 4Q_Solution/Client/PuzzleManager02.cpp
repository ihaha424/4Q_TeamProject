#include "pch.h"
#include "PuzzleManager02.h"

void PuzzleManager02::PreInitialize(const Engine::Modules& modules)
{
	PuzzleManager::PreInitialize(modules);
	_sync->SetSerialNumber(9003);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_02");
}

void PuzzleManager02::SetStart(const PlayMsg::PuzzleStart* msg)
{
}

void PuzzleManager02::SetFinish(const PlayMsg::PuzzleStart* msg)
{
}

void PuzzleManager02::SetInteract(const PlayMsg::InteractObject* msg)
{
}

void PuzzleManager02::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
