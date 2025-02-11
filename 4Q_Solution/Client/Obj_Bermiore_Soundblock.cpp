#include "pch.h"
#include "Obj_Bermiore_Soundblock.h"

Obj_Bermiore_Soundblock::Obj_Bermiore_Soundblock(const std::filesystem::path& meshPath,
	const std::filesystem::path& physicsPath):
	InteractObject(meshPath, physicsPath)
{
}

void Obj_Bermiore_Soundblock::Interact()
{

}

void Obj_Bermiore_Soundblock::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
}
