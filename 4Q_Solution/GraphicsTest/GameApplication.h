#pragma once
#include "TestWorld.h"

class GameApplication : public Engine::Application
{
public:
	explicit GameApplication(HINSTANCE instanceHandle);

protected:
	void DeclareInputActions(Engine::Input::IManager* inputManager) override;
	void Register(Engine::Content::IManager* contentManager) override;
	void PrepareInitialWorld(Engine::Content::Factory::World* worldFactory) override;

private:
	void DeclareMoveAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext);
	void DeclareCameraAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext);
};