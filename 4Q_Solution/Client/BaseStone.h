#pragma once
#include "InteractObejct.h"
#include "TriggerBox.h"
#include "Puzzle_00.h"

class BaseStone
	:public InteractObejct
{
public:
	explicit BaseStone(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~BaseStone() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

protected:
	Engine::GameState::IManager* myManager;
	unsigned int index;
};

