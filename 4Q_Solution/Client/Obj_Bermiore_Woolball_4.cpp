#include "pch.h"
#include "Obj_Bermiore_Woolball_4.h"

Obj_Bermiore_Woolball_4::Obj_Bermiore_Woolball_4(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath) :
	BaseWoolball((meshPath), (physicsPath))
{
}

void Obj_Bermiore_Woolball_4::Interact()
{
	if (_activate)
	{
		_index += _direction;
		if (_index == 2 || _index == 0)
			_direction *= -1;
		SendInteractToServer();
	}
}

void Obj_Bermiore_Woolball_4::PreInitialize(const Engine::Modules& modules)
{
	BaseWoolball::PreInitialize(modules);
	_sync->SetSerialNumber(12105);
	PreSetSoundProperty(1, L"Assets/Sounds/SFX_Bermiore_Ball_1.wav");
	PreSetSoundProperty(2, L"Assets/Sounds/SFX_Bermiore_Ball_2.wav");
	PreSetSoundProperty(3, L"Assets/Sounds/SFX_Bermiore_Ball_3.wav");
}

void Obj_Bermiore_Woolball_4::PostInitialize(const Engine::Modules& modules)
{
	BaseWoolball::PostInitialize(modules);
	PostSetSoundProperty(1, 5.f, 15.f);
	PostSetSoundProperty(2, 5.f, 15.f);
	PostSetSoundProperty(3, 5.f, 15.f);
}
void Obj_Bermiore_Woolball_4::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_01>(value);
	if (data._finish)
		_activate = false;
	if (data._start)
		_activate = true;
}
