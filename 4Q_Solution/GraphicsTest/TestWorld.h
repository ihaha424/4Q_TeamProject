#pragma once
#include "Player.h"
#include "GlobalLight.h"
#include "Terrain.h"
#include "SkyBox.h"

class TestWorld : public Engine::World
{
public:
	TestWorld() = default;

	void Prepare(Engine::Content::Factory::Object* objectFactory) override;
    
protected:
	void PreInitialize(const Engine::Modules& moduels) override;
	void PreUpdate(float deltaTime) override;
	void PostFixedUpdate() override;

private:
	Player* _player;
	GlobalLight* _light;
	Terrain* _terrain;
	SkyBox* _skyBox;

	int playerSerialNum = 0;
};

