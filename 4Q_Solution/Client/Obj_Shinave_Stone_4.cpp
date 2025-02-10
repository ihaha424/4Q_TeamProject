#include "pch.h"
#include "Obj_Shinave_Stone_4.h"

Obj_Shinave_Stone_4::Obj_Shinave_Stone_4(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: BaseStone(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
	index = 3;
}

void Obj_Shinave_Stone_4::Interact()
{
	auto stateOpt = myManager->GetData(L"Data");
	if (stateOpt)
	{
		auto data = std::any_cast<Puzzle_01>(*stateOpt);
		data.flag[index] = true;
		myManager->SetData(L"Data", data);
	}
}

void Obj_Shinave_Stone_4::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_01>(value);
	if (data.flag[index])
	{
		// 빛나기? 소리 나기?
	}
}
