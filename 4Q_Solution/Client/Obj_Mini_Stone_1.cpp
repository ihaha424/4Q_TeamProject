#include "pch.h"
#include "Obj_Mini_Stone_1.h"

Obj_Mini_Stone_1::Obj_Mini_Stone_1(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath):
	BaseMiniStone(meshPath, physicsPath)
{
}

void Obj_Mini_Stone_1::Interact()
{
	SendInteractToServer();
}

void Obj_Mini_Stone_1::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
