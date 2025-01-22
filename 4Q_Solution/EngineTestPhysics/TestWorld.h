#pragma once
#include "Player.h"

class TestWorld : public Engine::World
{
protected:
	void Addition() override;

private:
	Player _player;
};

