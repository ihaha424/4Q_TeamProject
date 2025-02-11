#pragma once
#include "InteractObject.h"
#include "Puzzle_04.h"

class Obj_Hide_Potion : public InteractObject
{
public:
	explicit Obj_Hide_Potion(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Hide_Potion() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void SendInteractToServer();

	void Interact() override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	Engine::Component::Synchronize* _sync;
};


