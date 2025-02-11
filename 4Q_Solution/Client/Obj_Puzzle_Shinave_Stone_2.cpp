#include "pch.h"
#include "Obj_Puzzle_Shinave_Stone_2.h"

Obj_Puzzle_Shinave_Stone_2::Obj_Puzzle_Shinave_Stone_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: BaseStone(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
	index = 1;
}

void Obj_Puzzle_Shinave_Stone_2::Interact()
{
	auto stateOpt = myManager->GetData(L"Data");
	if (stateOpt)
	{
		auto data = std::any_cast<Puzzle_00>(*stateOpt);
		data.flag[index] = true;
		myManager->SetData(L"Data", data);
	}
	SendInteractToServer();
}

void Obj_Puzzle_Shinave_Stone_2::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_00>(value);
	if (data.flag[index])
	{
		// 빛나기? 소리 나기?
	}
}