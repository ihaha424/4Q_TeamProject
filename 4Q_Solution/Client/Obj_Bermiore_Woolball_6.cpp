#include "pch.h"
#include "Obj_Bermiore_Woolball_6.h"

Obj_Bermiore_Woolball_6::Obj_Bermiore_Woolball_6(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	BaseWoolball(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}

void Obj_Bermiore_Woolball_6::Interact()
{
	if (_activate)
	{
		SendInteractToServer();
	}
}

void Obj_Bermiore_Woolball_6::PreInitialize(const Engine::Modules& modules)
{
	BaseWoolball::PreInitialize(modules);
	_sync->SetSerialNumber(12107);
	PreSetSoundProperty(1, L"Assets/Sounds/SFX_Bermiore_Ball_1.wav");
	PreSetSoundProperty(2, L"Assets/Sounds/SFX_Bermiore_Ball_2.wav");
	PreSetSoundProperty(3, L"Assets/Sounds/SFX_Bermiore_Ball_3.wav");
}

void Obj_Bermiore_Woolball_6::PostInitialize(const Engine::Modules& modules)
{
	BaseWoolball::PostInitialize(modules);
	PostSetSoundProperty(1, 5.f, 15.f);
	PostSetSoundProperty(2, 5.f, 15.f);
	PostSetSoundProperty(3, 5.f, 15.f);
}
void Obj_Bermiore_Woolball_6::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_01>(value);
	if (data._finish)
		_activate = false;
	if (data._start)
		_activate = true;
}
