#pragma once
#include "GlobalLight.h"
#include "Terrain.h"
#include "SkyBox.h"

#include "Ray.h"


#include "StaticObject.h"
#include "MapData.h"


class TestWorld : public Engine::World
{
public:
	TestWorld() = default;

	void Prepare(Engine::Content::Factory::Object* objectFactory) override;
    
protected:
	void PreInitialize(const Engine::Modules& moduels) override;
	void PreUpdate(float deltaTime) override;
	void PostUpdate(float deltaTime )override;
	void PostFixedUpdate() override;

private:
	Ray* _ray;
	//Live* _live;
	GlobalLight* _light;
	Terrain* _terrain;
	SkyBox* _skyBox;

	int playerSerialNum = 0;
	bool _dataLoad = false;

	Engine::Physics::IScene* mainScene;
	Engine::Physics::IScene* cameraScene;

public:
	void EnterAccept(const ConnectMsg::AddObject* msg);
	void CreatePlayer(const ConnectMsg::AddObject* msg);
	void CreateStaticObject(const ConnectMsg::AddObject* msg);
	void RequestData(const ConnectMsg::AddObject* msg);
};

