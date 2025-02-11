#include "pch.h"
#include "Obj_Puzzle_Mini_Stone_3.h"

Obj_Puzzle_Mini_Stone_3::Obj_Puzzle_Mini_Stone_3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	BaseMiniStone(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}

void Obj_Puzzle_Mini_Stone_3::Interact()
{
	SendInteractToServer();
}
