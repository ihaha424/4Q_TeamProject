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
	auto data = myManager->GetData(L"Data");
	if (data)
	{
		auto puzzle_01 = std::any_cast<Puzzle_01>(*data);

		puzzle_01._start = true;
		myManager->SetData(L"Data", puzzle_01);
	}
}

void PuzzleManager01::SetFinish(const PlayMsg::PuzzleStart* msg)
{
	auto data = myManager->GetData(L"Data");
	if (data)
	{
		auto puzzle_01 = std::any_cast<Puzzle_00>(*data);

		puzzle_01._start = true;
		myManager->SetData(L"Data", puzzle_01);
	}
}

void PuzzleManager01::SetInteract(const PlayMsg::InteractObject* msg)
{
}

void PuzzleManager01::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
