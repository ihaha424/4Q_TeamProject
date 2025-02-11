#pragma once
#include "StaticObject.h"

class Obj_Shinave_Platform_Spawn_3
	: public StaticObject
{
public:
	explicit Obj_Shinave_Platform_Spawn_3(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Shinave_Platform_Spawn_3() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void SetActive(const PlayMsg::ObjectActive* msg);

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;

	Engine::Component::Synchronize* _sync;
};
