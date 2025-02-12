#include "pch.h"
#include "NPC.h"

NPC::NPC(std::filesystem::path meshPath, Engine::Math::Matrix matrix):
	_meshPath(std::move(meshPath)),
	_worldMatrix(matrix),
	_skeletalMesh(nullptr),
	_animator(nullptr)
{
}

void NPC::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_skeletalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>(this);
	_animator = componentFactory->Clone<Engine::Component::Animator>(this);
}

void NPC::DisposeComponents()
{
	_skeletalMesh->Dispose();
	_animator->Dispose();
}

void NPC::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_skeletalMesh->SetFilePath(_meshPath);
	_skeletalMesh->SetMatrix(&_worldMatrix);
	_animator->SetSkeletalMesh(_skeletalMesh);
}

void NPC::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_skeletalMesh->SetPostEffectFlag(1);
	_animator->ChangeAnimation("rig|Anim_Idle");
}

