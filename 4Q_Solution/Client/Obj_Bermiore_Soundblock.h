#pragma once
#include "InteractObject.h"
#include "Puzzle_01.h"

class Obj_Bermiore_Soundblock : public InteractObject
{
public:
	explicit Obj_Bermiore_Soundblock(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Bermiore_Soundblock() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void SendInteractToServer();
	void PlaySound(const PlayMsg::InteractObject* msg);
	void Interact() override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
	void PostUpdate(float deltaTime) override;

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	Engine::Component::Synchronize* _sync;
	bool _activate = false;
	bool _isSound = false;
	float _deltaTime = 0;
	int _soundIndex = 0;
};

