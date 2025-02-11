#include "pch.h"
#include "Obj_Shinave_Stone_5.h"

Obj_Shinave_Stone_5::Obj_Shinave_Stone_5(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: BaseStone(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
	index = 4;
}

void Obj_Shinave_Stone_5::Interact()
{
	auto stateOpt = myManager->GetData(L"Data");
	if (stateOpt)
	{
		auto data = std::any_cast<Puzzle_01>(*stateOpt);
		data.flag[index] = true;
		myManager->SetData(L"Data", data);
	}
}

void Obj_Shinave_Stone_5::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_01>(value);
	if (data.flag[index])
	{
		// 빛나기? 소리 나기?
	}
}

