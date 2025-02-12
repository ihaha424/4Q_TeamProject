#pragma once
#include "BaseWoolball.h"

class Obj_Bermiore_Woolball_3 : public BaseWoolball
{
public:
	Obj_Bermiore_Woolball_3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Interact() override;
	void PreInitialize(const Engine::Modules& modules) override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;

protected:

};