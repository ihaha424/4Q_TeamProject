#pragma once
#include "InteractObject.h"
#include "Puzzle_01.h"

class BaseWoolball : public InteractObject
{
public:
	explicit BaseWoolball(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~BaseWoolball() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void SendInteractToServer();
protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	Engine::Component::Synchronize* _sync;

	int _pos[3];
	int _index;
	int direction;
	bool _activate;
};


