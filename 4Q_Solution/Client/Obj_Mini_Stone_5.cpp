#include "pch.h"
#include "Obj_Mini_Stone_5.h"

Obj_Mini_Stone_5::Obj_Mini_Stone_5(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath):
	BaseMiniStone(meshPath, physicsPath)
{
}

void Obj_Mini_Stone_5::Interact()
{
	SendInteractToServer();
}

void Obj_Mini_Stone_5::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
