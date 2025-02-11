#include "pch.h"
#include "Obj_Shinave_Stone_3.h"

Obj_Shinave_Stone_3::Obj_Shinave_Stone_3(const std::filesystem::path& meshPath,
	const std::filesystem::path& physicsPath):
	BaseStone(meshPath, physicsPath)
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
}

