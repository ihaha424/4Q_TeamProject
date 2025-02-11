#pragma once
#include "InteractObject.h"
#include "Puzzle_01.h"

class BaseWoolball : public InteractObject
{
public:
	explicit BaseWoolball(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~BaseWoolball() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void SendInteractToServer();
protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	Engine::GameState::IManager* _gameStateManager;
	unsigned int _index;

	Engine::Component::Synchronize* _sync;
};


