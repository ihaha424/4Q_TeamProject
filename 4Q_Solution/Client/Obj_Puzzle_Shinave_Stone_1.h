#pragma once
#include "BaseStone.h"

class Obj_Puzzle_Shinave_Stone_1
	: public BaseStone
{
public:
	explicit Obj_Puzzle_Shinave_Stone_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Puzzle_Shinave_Stone_1() = default;

	// BaseStone을(를) 통해 상속됨
	void InteractObject() override;

	// BaseStone을(를) 통해 상속됨
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
};

