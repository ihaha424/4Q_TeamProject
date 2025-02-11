#include "pch.h"
#include "Obj_Mini_Stone_4.h"

Obj_Mini_Stone_4::Obj_Mini_Stone_4(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath):
	BaseMiniStone(meshPath, physicsPath)
{
}

void Obj_Mini_Stone_4::Interact()
{
	SendInteractToServer();
}

void Obj_Mini_Stone_4::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
