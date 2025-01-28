#pragma once
#include "Player.h"
#include "GlobalLight.h"
#include "Terrain.h"
#include "RemotePlayer.h"

class ConnectMsg::EnterAccept;

class TestWorld : public Engine::World
{
public:
	TestWorld() = default;

	void Prepare(Engine::Content::Factory::Object* objectFactory) override;
	void EnterAccept(const ConnectMsg::EnterAccept* msg);
	void SyncOtherPlayer(const ConnectMsg::SyncPlayer* msg);
    
protected:
	void PreInitialize(const Engine::Modules& moduels) override;
	void PreUpdate(float deltaTime) override;
	void PostFixedUpdate() override;

private:
	Player* _player;
	RemotePlayer* _remote;
	GlobalLight* _light;
	Terrain* _terrain;

	int playerSerialNum = 0;
};

