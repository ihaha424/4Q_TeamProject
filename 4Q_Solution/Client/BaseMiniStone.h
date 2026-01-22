#pragma once
#include "InteractObject.h"

class BaseMiniStone : public InteractObject
{
public:
	BaseMiniStone(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void SendInteractToServer();
protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	Engine::GameState::IManager* _gameStateManager;
	unsigned int _index;

	Engine::Component::Synchronize* _sync;
};

