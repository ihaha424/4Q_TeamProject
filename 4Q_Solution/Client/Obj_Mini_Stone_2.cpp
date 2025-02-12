#include "pch.h"
#include "Obj_Mini_Stone_2.h"

Obj_Mini_Stone_2::Obj_Mini_Stone_2(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath):
	BaseMiniStone(meshPath, physicsPath)
{
}

void Obj_Mini_Stone_2::Interact()
{
	SendInteractToServer();
}

void Obj_Mini_Stone_2::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
