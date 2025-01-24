 #pragma once
#include "Player.h"
#include "GlobalLight.h"
#include "Terrain.h"

class TestWorld : public Engine::World
{
protected:
	void Addition() override;

private:
	Player _player;
	RemotePlayer _remote;
	GlobalLight _light;
	Terrain _terrain;
};

