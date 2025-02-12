#include "pch.h"
#include "PuzzleManager04.h"

void PuzzleManager04::PreInitialize(const Engine::Modules& modules)
{
	PuzzleManager::PreInitialize(modules);
	_sync->SetSerialNumber(9005);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_04");
}

void PuzzleManager04::SetStart(const PlayMsg::PuzzleStart* msg)
{
}

void PuzzleManager04::SetFinish(const PlayMsg::PuzzleStart* msg)
{
}

void PuzzleManager04::SetInteract(const PlayMsg::InteractObject* msg)
{
}

void PuzzleManager04::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
