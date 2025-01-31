#pragma once
#include "Player.h"
#include "GlobalLight.h"
#include "Terrain.h"
#include "RemotePlayer.h"
#include "Cube.h"
#include "Sphere.h"

class TestWorld : public Engine::World
{
public:
	TestWorld() = default;

	void Prepare(Engine::Content::Factory::Object* objectFactory) override;
	void EnterAccept(int num);
	void SyncOtherPlayer(int num);
	void CreateStaticObject(int num);
	void RequestData(int num);
    
protected:
	void PreInitialize(const Engine::Modules& moduels) override;
	void PreUpdate(float deltaTime) override;
	void PostFixedUpdate() override;

private:
	Player* _player;
	RemotePlayer* _remote;
	GlobalLight* _light;
	Terrain* _terrain;

	
	std::vector<Cube*> _cubes;

	bool _loadComplete = false;
private:
	Engine::Physics::IScene* testPhysicsScene;
};

