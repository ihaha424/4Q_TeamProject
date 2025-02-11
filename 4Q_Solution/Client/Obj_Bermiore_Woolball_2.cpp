#include "pch.h"
#include "Obj_Bermiore_Woolball_2.h"

Obj_Bermiore_Woolball_2::Obj_Bermiore_Woolball_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	BaseWoolball(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
	_index = 0;
}

void Obj_Bermiore_Woolball_2::Interact()
{
	SendInteractToServer();
}

void Obj_Bermiore_Woolball_2::PreInitialize(const Engine::Modules& modules)
{
}

void Obj_Bermiore_Woolball_2::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
