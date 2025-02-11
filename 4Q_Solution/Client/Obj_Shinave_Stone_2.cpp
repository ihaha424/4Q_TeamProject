#include "pch.h"
#include "Obj_Shinave_Stone_2.h"

Obj_Shinave_Stone_2::Obj_Shinave_Stone_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: BaseStone(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
	index = 1;
}

void Obj_Shinave_Stone_2::Interact()
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

void Obj_Shinave_Stone_2::PreInitialize(const Engine::Modules& modules)
{
	BaseStone::PreInitialize(modules);
	_sync->SetSerialNumber(11107);
}

void Obj_Shinave_Stone_2::DataChangeCallBack(const std::wstring& name, const std::any& value)
{

}