#pragma once

class Terrain : public Engine::Object
{
public:
	Terrain();

protected:
	void Addition() override;
	void PostInitialize() override;

private:
	Engine::Component::StaticMesh _staticMesh;
	Engine::Math::Matrix _matrix;
};

