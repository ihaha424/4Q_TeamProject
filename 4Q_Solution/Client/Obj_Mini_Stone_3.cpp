#include "pch.h"
#include "Obj_Mini_Stone_3.h"

Obj_Mini_Stone_3::Obj_Mini_Stone_3(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath):
	BaseMiniStone(meshPath, physicsPath)
{
}

void Obj_Mini_Stone_3::Interact()
{
	SendInteractToServer();
}

void Obj_Mini_Stone_3::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
