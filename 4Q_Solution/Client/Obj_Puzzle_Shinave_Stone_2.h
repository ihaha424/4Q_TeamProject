#pragma once
#include "BaseStone.h"

class Obj_Puzzle_Shinave_Stone_2
	: public BaseStone
{
public:
	explicit Obj_Puzzle_Shinave_Stone_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Puzzle_Shinave_Stone_2() = default;

	void Interact() override;

	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
};