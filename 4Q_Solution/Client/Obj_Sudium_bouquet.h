#pragma once
#include "InteractObject.h"

class Obj_Sudium_bouquet : public InteractObject
{
public:
	explicit Obj_Sudium_bouquet(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);

	virtual ~Obj_Sudium_bouquet() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void Interact() override;
protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	Engine::GameState::IManager* _gameStateManager;
	unsigned int _index;

	Engine::Component::Synchronize* _sync;

};

