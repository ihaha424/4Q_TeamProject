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
	void InteractCallback(const PlayMsg::InteractObject* msg);

	Engine::Component::Synchronize* _sync;

	float _pos[3];
	int _posIndex;
	int _index;
	int _direction;
	bool _activate;

	const static int initPosition[6];
	const static int initDirection[6];
	const static int thirdPos[6];
	const static int muteValue[6];

	static int index;
};


