#pragma once
constexpr int BoxCount = 4;

struct Puzzle_04
{
	bool _start;
	bool _finish;
	bool _trigger[BoxCount];
	Engine::Math::Vector3* livePos;
};

