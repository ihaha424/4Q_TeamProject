#include "pch.h"
#include "Obj_Shinave_Stone_3.h"

Obj_Shinave_Stone_3::Obj_Shinave_Stone_3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: BaseStone(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
	index = 2;
}

void Obj_Shinave_Stone_3::Interact()
{
	if (activate)
	{
		auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
		if (!isData)
			return;
		auto data = std::any_cast<GameCoreData>(*isData);
		player = data.player;
		if (player == 2)
		{
			auto stateOpt = myManager->GetData(L"Data");
			if (stateOpt)
			{
				auto data = std::any_cast<Puzzle_00>(*stateOpt);
				data.flag[index] = true;
				myManager->SetData(L"Data", data);
			}
			SendInteractToServer();
			activate = false;
		}
	}
}

void Obj_Shinave_Stone_3::PreInitialize(const Engine::Modules& modules)
{
	BaseStone::PreInitialize(modules);
	_sync->SetSerialNumber(11108);
}

void Obj_Shinave_Stone_3::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_00>(value);
	if (data.flag[index])
	{
		// 빛나기? 소리 나기?
	}
}

