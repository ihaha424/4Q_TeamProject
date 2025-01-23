#pragma once
#include "TestWorld.h"

class GameApplication : public Engine::Application
{
public:
	explicit GameApplication(HINSTANCE instanceHandle);

protected:
	void DeclareInputActions(Engine::Input::IManager* inputManager) override;
	void Register(Engine::Load::IManager* loadManager) override;

	void Addition() override;
	void InitializeContents() override;

private:
	TestWorld _world;
};

