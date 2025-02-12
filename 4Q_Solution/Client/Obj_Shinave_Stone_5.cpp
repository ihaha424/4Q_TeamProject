#include "pch.h"
#include "Obj_Shinave_Stone_5.h"

Obj_Shinave_Stone_5::Obj_Shinave_Stone_5(const std::filesystem::path& meshPath,
	const std::filesystem::path& physicsPath):
	BaseStone(meshPath, physicsPath)
{
	index = 4;
}

void Obj_Shinave_Stone_5::Interact()
{
	if (activate)
	{
		auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
		if (!isData)
			return;
		auto data = std::any_cast<GameCoreData>(*isData);
		player = data.player;
		if (player == 2 || data.player == 3)
		{
			SendInteractToServer();
			activate = false;
		}
	}
}

void Obj_Shinave_Stone_5::PreInitialize(const Engine::Modules& modules)
{
	BaseStone::PreInitialize(modules);
	_sync->SetSerialNumber(11110);
}

void Obj_Shinave_Stone_5::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	activate = true;
}

