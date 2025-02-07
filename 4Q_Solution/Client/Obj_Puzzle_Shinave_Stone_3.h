#pragma once
#include "BaseStone.h"

class Obj_Puzzle_Shinave_Stone_3
	: public BaseStone
{
public:
	explicit Obj_Puzzle_Shinave_Stone_3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Puzzle_Shinave_Stone_3() = default;

};

