#pragma once
#include "BaseMiniStone.h"

class Obj_Puzzle_Mini_Stone_3 : public BaseMiniStone
{
public:
	explicit Obj_Puzzle_Mini_Stone_3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Interact() override;


protected:
};