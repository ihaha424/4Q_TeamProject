#include "pch.h"
#include "Obj_Shinave_Stone_4.h"

Obj_Shinave_Stone_4::Obj_Shinave_Stone_4(const std::filesystem::path& meshPath,
	const std::filesystem::path& physicsPath):
	BaseStone(meshPath, physicsPath)
{
	index = 3;
}

void Obj_Shinave_Stone_4::Interact()
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

void Obj_Shinave_Stone_4::PreInitialize(const Engine::Modules& modules)
{
	BaseStone::PreInitialize(modules);
	_sync->SetSerialNumber(11109);
	PreSetSoundProperty(L"Assets/Sounds/SFX_Shinave_Stone_Correct_1.wav");

	_trigger->BindBeginInteraction([this]()
		{
			auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
			if (!isData)
				return;
			auto data = std::any_cast<GameCoreData>(*isData);
			if (data.player == 2 || data.player == 3)
			{
				_staticMesh->SetActiveDraw(true);
				_sound->Play();
			}
		});
}

void Obj_Shinave_Stone_4::PostInitialize(const Engine::Modules& modules)
{
	BaseStone::PostInitialize(modules);
	PostSetSoundProperty(1.4f, 8.5f);
}
void Obj_Shinave_Stone_4::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	activate = true;
}
