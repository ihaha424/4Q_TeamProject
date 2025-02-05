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
	void PostFixedUpdate() override;

private:
	Ray* _ray;
	GlobalLight* _light;
	Terrain* _terrain;
	SkyBox* _skyBox;

	int playerSerialNum = 0;
};

