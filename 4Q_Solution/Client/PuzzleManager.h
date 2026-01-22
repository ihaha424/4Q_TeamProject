#pragma once

class PuzzleManager
	: public Engine::Object
{
public:
	explicit PuzzleManager();
	virtual ~PuzzleManager() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	virtual void SetStart(const PlayMsg::PuzzleStart* msg) = 0;
	virtual void SetFinish(const PlayMsg::PuzzleStart* msg) = 0;
	virtual void SetInteract(const PlayMsg::InteractObject* msg) = 0;

	virtual void DataChangeCallBack(const std::wstring& name, const std::any& value) = 0;


protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;

protected:
	Engine::Component::Synchronize* _sync;
	Engine::GameState::IManager* myManager;
	
};

