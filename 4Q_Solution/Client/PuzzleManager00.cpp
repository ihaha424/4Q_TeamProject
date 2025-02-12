#include "pch.h"
#include "PuzzleManager00.h"

void PuzzleManager00::PreInitialize(const Engine::Modules& modules)
{
	PuzzleManager::PreInitialize(modules);
	_sync->SetSerialNumber(9001);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_00");
}

void PuzzleManager00::SetStart(const PlayMsg::PuzzleStart* msg)
{
	auto data = myManager->GetData(L"Data");
	if (data)
	{
		auto puzzle_01 = std::any_cast<Puzzle_00>(*data);

		puzzle_01._start = true;
		myManager->SetData(L"Data", puzzle_01);
	}
}

void PuzzleManager00::SetFinish(const PlayMsg::PuzzleStart* msg)
{
	auto data = myManager->GetData(L"Data");
	if (data)
	{
		auto puzzle_01 = std::any_cast<Puzzle_00>(*data);

			puzzle_01._start = true;
			myManager->SetData(L"Data", puzzle_01);
	}
}

void PuzzleManager00::SetInteract(const PlayMsg::InteractObject* msg)
{
}

void PuzzleManager00::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
