#include "pch.h"
#include "PuzzleManager01.h"

void PuzzleManager01::PreInitialize(const Engine::Modules& modules)
{
	PuzzleManager::PreInitialize(modules);
	_sync->SetSerialNumber(9002);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_01");
}

void PuzzleManager01::SetStart(const PlayMsg::PuzzleStart* msg)
{
}

void PuzzleManager01::SetFinish(const PlayMsg::PuzzleStart* msg)
{
}

void PuzzleManager01::SetInteract(const PlayMsg::InteractObject* msg)
{
}

void PuzzleManager01::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
