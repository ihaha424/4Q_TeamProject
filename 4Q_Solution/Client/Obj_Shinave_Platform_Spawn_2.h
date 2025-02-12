#pragma once
#include "StaticObject.h"

class Obj_Shinave_Platform_Spawn_2
	: public StaticObject
{
public:
	Obj_Shinave_Platform_Spawn_2(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Shinave_Platform_Spawn_2() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void SetActive(const PlayMsg::ObjectActive* msg);

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;

	Engine::Component::Synchronize* _sync;
	Engine::Component::Effect3DSound* _sound;
};
