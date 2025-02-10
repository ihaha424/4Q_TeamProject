#pragma once
#include "BaseStone.h"

class Obj_Shinave_Stone_3
	: public BaseStone
{
public:
	explicit Obj_Shinave_Stone_3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Shinave_Stone_3() = default;


	// BaseStone을(를) 통해 상속됨
	void Interact() override;

	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;

};

