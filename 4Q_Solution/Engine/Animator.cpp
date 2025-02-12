#include "pch.h"
#include "Animator.h"
#include "GEGraphicsManager.h"

void Engine::Component::Animator::Initialize(const Modules& modules)
{
	GraphicsComponent::Initialize(modules);
	auto animationSystem = _graphicsManager->GetAnimationSystem();
	animationSystem->CreateAnimator(_skeletalMesh->_geMeshRenderer, &_geAnimator);
}

void Engine::Component::Animator::Attach()
{
	GraphicsComponent::Attach();
	auto animationSystem = _graphicsManager->GetAnimationSystem();
	animationSystem->RegisterAnimator(_geAnimator);
}

void Engine::Component::Animator::Detach()
{
	GraphicsComponent::Detach();
	auto animationSystem = _graphicsManager->GetAnimationSystem();
	animationSystem->UnRegisterAnimator(_geAnimator);
}

void Engine::Component::Animator::Finalize()
{
	_geAnimator->Release();
}

void Engine::Component::Animator::SetSkeletalMesh(SkeletalMesh* skeletalMesh)
{
	_skeletalMesh = skeletalMesh;
}

void Engine::Component::Animator::ChangeAnimation(const char* animation) const
{
	_geAnimator->ChangeAnimation(animation);
}

void Engine::Component::Animator::ChangeAnimation(const char* animation, unsigned int id) const
{
	_geAnimator->ChangeAnimation(animation, id);
}

void Engine::Component::Animator::SyncPartialAnimation(unsigned int parentID, unsigned int childID) const
{
	_geAnimator->SyncPartialAnimation(parentID, childID);
}

bool Engine::Component::Animator::IsLastFrame(float interval, unsigned int id) const
{
	return _geAnimator->IsLastFrame(interval, id);
}

void Engine::Component::Animator::SetUpSplitBone(unsigned int maxSplit) const
{
	_geAnimator->SetUpSplitBone(maxSplit);
}

void Engine::Component::Animator::SplitBone(unsigned int id, const char* boneName) const
{
	_geAnimator->SplitBone(id, boneName);
}

void Engine::Component::Animator::SetAnimationSpeed(float speed) const
{
	_geAnimator->SetAnimationSpeed(speed);
}

void Engine::Component::Animator::MakeParent(const char* parent, const char* child) const
{
	_geAnimator->MakeParent(parent, child);
}

void Engine::Component::Animator::GetSkeletonMatrix(const char* bone, Engine::Math::Matrix** out) const
{
	_geAnimator->GetSkeletonMatrix(bone, (GE::Matrix4x4**)out);
}
