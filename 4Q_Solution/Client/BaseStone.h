#pragma once
#include "StaticObject.h"
#include "TriggerBox.h"

class BaseStone
	:public StaticObject
{
public:
	explicit BaseStone(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~BaseStone() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;

protected:
	TriggerBox* _trigger;
};

