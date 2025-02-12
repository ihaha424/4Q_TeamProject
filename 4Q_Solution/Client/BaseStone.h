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
	void SetSoundProperty(std::filesystem::path path, float min, float max);
protected:
	Engine::GameState::IManager* myManager;
	unsigned int index;

	Engine::Component::Synchronize* _sync;
	Engine::Component::Effect3DSound* _sound;
	int player;
	bool activate = false;
};

