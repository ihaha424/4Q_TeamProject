#pragma once
#include "InteractObject.h"
#include "TriggerBox.h"
#include "Puzzle_01.h"

class BaseStone
	:public InteractObject
{
public:
	explicit BaseStone(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~BaseStone() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	void SendInteractToServer();
protected:
	Engine::GameState::IManager* myManager;
	unsigned int index;

	Engine::Component::Synchronize* _sync;
};

