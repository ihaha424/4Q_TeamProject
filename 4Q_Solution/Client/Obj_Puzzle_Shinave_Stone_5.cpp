#include "pch.h"
#include "Obj_Puzzle_Shinave_Stone_5.h"

Obj_Puzzle_Shinave_Stone_5::Obj_Puzzle_Shinave_Stone_5(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: BaseStone(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
	index = 4;
}

void Obj_Puzzle_Shinave_Stone_5::InteractObject()
{
	auto stateOpt = myManager->GetData(L"puzzle_00");
	if (stateOpt)
	{
		auto data = std::any_cast<Puzzle_00>(*stateOpt);
		data.flag[index] = true;
		myManager->SetData(L"puzzle_00", data);
	}
}

void Obj_Puzzle_Shinave_Stone_5::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_00>(value);
	if (data.flag[index])
	{
		// 빛나기? 소리 나기?
	}
}

