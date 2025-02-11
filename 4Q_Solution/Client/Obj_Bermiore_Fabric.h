#pragma once
#include "InteractObject.h"

class Obj_Bermiore_Fabric : public InteractObject
{
public:
	explicit Obj_Bermiore_Fabric(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void Interact() override;
private:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	Engine::GameState::IManager* _gameStateManager;
	unsigned int _index;

	Engine::Component::Synchronize* _sync;
};

