#pragma once

enum class PlayerEnum
{
	Ray = 1,
	Live = 2,
	Developer = 3
};

struct GameCoreData
{
	int player = 0; // 레이 1, 리브 2
	int dialogId = 0;
	int puzzleId = 0;
};
