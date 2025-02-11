#include "pch.h"
#include "Obj_Bermiore_Woolball_3.h"

Obj_Bermiore_Woolball_3::Obj_Bermiore_Woolball_3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	BaseWoolball(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
	_index = 0;
}

void Obj_Bermiore_Woolball_3::Interact()
{
	SendInteractToServer();
}
