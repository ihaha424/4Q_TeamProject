#pragma once
#include "Player.h"
#include "GlobalLight.h"
#include "Terrain.h"

class TestWorld : public Engine::World
{
public:
	TestWorld() = default;

	void Prepare(Engine::Content::Factory::Object* objectFactory) override;

private:
	Player* _player;
	RemotePlayer* _remote;
	GlobalLight* _light;
	Terrain* _terrain;
};

