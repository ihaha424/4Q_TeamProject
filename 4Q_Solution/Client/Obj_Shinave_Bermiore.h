#pragma once
#include "InteractObject.h"
#include "Puzzle_01.h"

class Obj_Shinave_Bermiore
	:public InteractObject
{
public:
	explicit Obj_Shinave_Bermiore(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Shinave_Bermiore() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void PreInitialize(const Engine::Modules& modules) override;

protected:
	void DisposeComponents() override;

	void SendInteractToServer();

	Engine::Component::Synchronize* _sync;
	int player;

	// InteractObject을(를) 통해 상속됨
	void Interact() override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
};
