#pragma once
constexpr int BoxCount = 8;//?

struct Puzzle_04
{
	bool _start = false;
	bool _finish = false;
	bool _trigger[BoxCount]{};
	Engine::Math::Vector3* livePos;
};

