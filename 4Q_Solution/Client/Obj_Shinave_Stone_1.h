#pragma once
#include "BaseStone.h"

class Obj_Shinave_Stone_1
	: public BaseStone
{
public:
	Obj_Shinave_Stone_1(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Shinave_Stone_1() = default;

	void Interact() override;
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;

	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
};