#include "pch.h"
#include "Obj_Puzzle_Mini_Stone_2.h"
Obj_Puzzle_Mini_Stone_2::Obj_Puzzle_Mini_Stone_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	BaseMiniStone(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}

void Obj_Puzzle_Mini_Stone_2::Interact()
{
}
