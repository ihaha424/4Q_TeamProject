#pragma once
#include "Player.h"
#include "GlobalLight.h"
#include "Terrain.h"

class TestWorld : public Engine::World
{
protected:
	void Addition() override;

	void PreInitialize() override;
	void PreUpdate(float deltaTime) override;
	void PostFixedUpdate() override;

private:
	Player _player;
	TestPlayer _testPlayer;
	GlobalLight _light;
	Terrain _terrain;

	int playerSerialNum = 0;
};

