#pragma once
#include "InteractObject.h"

class BaseMiniStone : public InteractObject
{
public:
	explicit BaseMiniStone(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~BaseMiniStone() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void SendInteractToServer();
protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	Engine::GameState::IManager* _gameStateManager;
	unsigned int _index;

	Engine::Component::Synchronize* _sync;
};

