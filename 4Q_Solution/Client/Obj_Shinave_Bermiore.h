#pragma once
#include "InteractObject.h"
#include "Puzzle_01.h"

class Obj_Shinave_Bermiore
	:public InteractObject
{
public:
	Obj_Shinave_Bermiore(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void PreInitialize(const Engine::Modules& modules) override;

protected:
	void DisposeComponents() override;

	void SendInteractToServer();

	Engine::Component::Synchronize* _sync;
	int player;
	bool _activate = false;

	// InteractObject을(를) 통해 상속됨
	void Interact() override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
};
