#pragma once
#include "BaseWoolball.h"

class Obj_Bermiore_Woolball_5 : public BaseWoolball
{
public:
	Obj_Bermiore_Woolball_5(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);

	void Interact() override;
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;

protected:

};