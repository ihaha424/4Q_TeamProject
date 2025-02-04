#pragma once
#include "TestWorld.h"

class GameApplication : public Engine::Application
{
public:
	explicit GameApplication(HINSTANCE instanceHandle);

protected:
	void DeclareInputActions(Engine::Input::IManager* inputManager) override;
	void Addition() override;
	void InitializeContents() override;

private:
	void DeclareMoveAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext);
	void DeclareCameraAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext);

	TestWorld _world;
};

