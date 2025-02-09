#pragma once
#include "BaseStone.h"

class Obj_Puzzle_Shinave_Stone_5
	: public BaseStone
{
public:
	explicit Obj_Puzzle_Shinave_Stone_5(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Puzzle_Shinave_Stone_5() = default;

};

