#include "pch.h"
#include "Animator.h"
#include "GEGraphicsManager.h"

Engine::Component::Animator::Animator(SkeletalMesh* skeletalMesh)
	: _geAnimator(nullptr)
	, _skeletalMesh(skeletalMesh)
{
}

void Engine::Component::Animator::Initialize()
{
	Component::Initialize();
	auto animationSystem = _graphicsManager->GetAnimationSystem();
	animationSystem->CreateAnimator(_skeletalMesh->_geMeshRenderer, &_geAnimator);
}

void Engine::Component::Animator::Attach()
{
	Component::Attach();
	auto animationSystem = _graphicsManager->GetAnimationSystem();
	animationSystem->RegisterAnimator(_geAnimator);
}

void Engine::Component::Animator::Detach()
{
	Component::Detach();
	auto animationSystem = _graphicsManager->GetAnimationSystem();
	animationSystem->UnRegisterAnimator(_geAnimator);
}

void Engine::Component::Animator::Finalize()
{
	_geAnimator->Release();
}

void Engine::Component::Animator::ChangeAnimation(const char* animation) const
{
	_geAnimator->ChangeAnimation(animation);
}

void Engine::Component::Animator::ChangeAnimation(const char* animation, const unsigned int ID) const
{
	_geAnimator->ChangeAnimation(animation, ID);
}

bool Engine::Component::Animator::IsLastFrame(float interval) const
{
	return _geAnimator->IsLastFrame(interval);
}

void Engine::Component::Animator::SetUpSplitBone(const unsigned int maxSplit) const
{
	_geAnimator->SetUpSplitBone(maxSplit);
}

void Engine::Component::Animator::SplitBone(const unsigned int ID, const char* boneName) const
{
	_geAnimator->SplitBone(ID, boneName);
}
