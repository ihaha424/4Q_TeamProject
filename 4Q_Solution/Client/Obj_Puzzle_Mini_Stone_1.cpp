#include "pch.h"
#include "Obj_Puzzle_Mini_Stone_1.h"

Obj_Puzzle_Mini_Stone_1::Obj_Puzzle_Mini_Stone_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	BaseMiniStone(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}

void Obj_Puzzle_Mini_Stone_1::Interact()
{
	SendInteractToServer();
}
