#pragma once
#include "Player.h"

class TestWorld : public Engine::World
{
protected:
	void PreInitialize() override;

private:
	Player _player;
};

