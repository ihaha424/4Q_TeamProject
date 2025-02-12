#include "pch.h"
#include "Obj_Bermiore_Woolball_4.h"

Obj_Bermiore_Woolball_4::Obj_Bermiore_Woolball_4(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	BaseWoolball(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}

void Obj_Bermiore_Woolball_4::Interact()
{
	if (_activate)
	{
		_index += direction;
		if (_index == 2 || _index == 0)
			direction *= -1;
		SendInteractToServer();
	}
}

void Obj_Bermiore_Woolball_4::PreInitialize(const Engine::Modules& modules)
{
	BaseWoolball::PreInitialize(modules);
	_sync->SetSerialNumber(12105);
}

void Obj_Bermiore_Woolball_4::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_01>(value);
	if (data.isFinish)
		_activate = false;
}
