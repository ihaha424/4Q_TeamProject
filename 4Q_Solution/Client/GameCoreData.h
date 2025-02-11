#pragma once


struct GameCoreData
{
	int player = 0; // 레이 1, 리브 2
	int dialogId = 0;
	int puzzleId = 0;
};

class GameCoreObject
	: public Engine::Object
{
public:
	explicit GameCoreObject();
	virtual ~GameCoreObject() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	void SendInteractToServer();
protected:
	Engine::Component::Synchronize* _sync;
};

