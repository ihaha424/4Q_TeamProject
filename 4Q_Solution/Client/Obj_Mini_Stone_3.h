#pragma once
#include "BaseMiniStone.h"

class Obj_Mini_Stone_3 : public BaseMiniStone
{
public:
	Obj_Mini_Stone_3(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);

	void Interact() override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;

protected:
};

