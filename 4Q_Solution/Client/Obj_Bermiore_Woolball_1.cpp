#include "pch.h"
#include "Obj_Bermiore_Woolball_1.h"

Obj_Bermiore_Woolball_1::Obj_Bermiore_Woolball_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	BaseWoolball(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
	_index = 0;
}

void Obj_Bermiore_Woolball_1::Interact()
{
	SendInteractToServer();
}
