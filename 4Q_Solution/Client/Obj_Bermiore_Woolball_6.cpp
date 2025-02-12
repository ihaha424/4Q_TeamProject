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
		_index += direction;
		if (_index == 2 || _index == 0)
			direction *= -1;
		SendInteractToServer();
	}
}

void Obj_Bermiore_Woolball_6::PreInitialize(const Engine::Modules& modules)
{
	BaseWoolball::PreInitialize(modules);
	_sync->SetSerialNumber(12102);
}

void Obj_Bermiore_Woolball_6::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_01>(value);
	if (data._finish)
		_activate = false;
	if (data._start)
		_activate = true;
}
