 #pragma once
#include "Player.h"
#include "GlobalLight.h"
#include "Terrain.h"
#include "RemotePlayer.h"

class ConnectMsg::EnterAccept;

class TestWorld : public Engine::World
{
public:
	void SyncOtherPlayer(const ConnectMsg::SyncPlayer* msg);
protected:
	void Addition() override;

	void PreInitialize() override;
	void PreUpdate(float deltaTime) override;
	void PostFixedUpdate() override;

private:
	Player _player;
	RemotePlayer _remote;
	GlobalLight _light;
	Terrain _terrain;

	int playerSerialNum = 0;
};

