#include "pch.h"
#include "NPC_Hide.h"

NPC_Hide::NPC_Hide():
	_meshPath(L"Assets/Models/NPC_Ornoa.fbx"),
	_worldMatrix(Engine::Math::Matrix::CreateScale(0.1f,0.1f,0.1f)),
	_skeletalMesh(nullptr),
	_animator(nullptr)
{
}

void NPC_Hide::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_skeletalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>(this);
	_animator = componentFactory->Clone<Engine::Component::Animator>(this);
}

void NPC_Hide::DisposeComponents()
{
	_skeletalMesh->Dispose();
	_animator->Dispose();
}

void NPC_Hide::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

	_skeletalMesh->SetFilePath(_meshPath);
	_skeletalMesh->SetMatrix(&_worldMatrix);
	_animator->SetSkeletalMesh(_skeletalMesh);
}

void NPC_Hide::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_skeletalMesh->SetPostEffectFlag(1);
	//_animator->ChangeAnimation("rig|Anim_Idle");
}
