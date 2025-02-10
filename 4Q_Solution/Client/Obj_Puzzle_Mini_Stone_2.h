#pragma once
#include "BaseMiniStone.h"

class Obj_Puzzle_Mini_Stone_2 : public BaseMiniStone
{
public:
	explicit Obj_Puzzle_Mini_Stone_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Interact() override;


protected:
};