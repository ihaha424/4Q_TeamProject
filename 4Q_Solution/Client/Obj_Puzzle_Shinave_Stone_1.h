#pragma once
#include "BaseStone.h"

class Obj_Puzzle_Shinave_Stone_1
	: public BaseStone
{
public:
	explicit Obj_Puzzle_Shinave_Stone_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Puzzle_Shinave_Stone_1() = default;

	void PostInitialize(const Engine::Modules& modules) override;

};

