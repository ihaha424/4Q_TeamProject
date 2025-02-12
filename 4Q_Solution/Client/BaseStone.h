#pragma once
#include "InteractObject.h"
#include "TriggerBox.h"
#include "Puzzle_01.h"
#include "GameCoreData.h"
#include "Application.h"

class BaseStone
	:public InteractObject
{
public:
	BaseStone(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
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
	int player;
	bool activate = false;
};

