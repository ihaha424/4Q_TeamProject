#include "pch.h"
#include "PuzzleManager03.h"

void PuzzleManager03::PreInitialize(const Engine::Modules& modules)
{
	PuzzleManager::PreInitialize(modules);
	_sync->SetSerialNumber(9004);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_03");
}

void PuzzleManager03::SetStart(const PlayMsg::PuzzleStart* msg)
{
}

void PuzzleManager03::SetFinish(const PlayMsg::PuzzleStart* msg)
{
}

void PuzzleManager03::SetInteract(const PlayMsg::InteractObject* msg)
{
}

void PuzzleManager03::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
