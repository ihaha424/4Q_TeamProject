#include "pch.h"
#include "AnimationSystem.h"

void Engine::Manager::GraphicsSystem::AnimationSystem::Initialize(GE::IAnimationSystem* animationSystem,
	const unsigned int threadCount)
{
	assert(animationSystem != nullptr);
	assert(_animationSystem == nullptr);
	_animationSystem = animationSystem;
	_animationSystem->Initialize(threadCount);
}

void Engine::Manager::GraphicsSystem::AnimationSystem::Update(const float deltaTime) const
{
	assert(_animationSystem != nullptr);
	_animationSystem->Update(deltaTime);
}

void Engine::Manager::GraphicsSystem::AnimationSystem::Finalize()
{
	Utility::SafeRelease()(&_animationSystem);
}

void Engine::Manager::GraphicsSystem::AnimationSystem::CreateAnimator(GE::IMeshRenderer* meshRenderer,
	GE::IAnimator** outAnimator) const
{
	assert(_animationSystem != nullptr);
	_animationSystem->CreateAnimator(meshRenderer, outAnimator);
}

void Engine::Manager::GraphicsSystem::AnimationSystem::RegisterAnimator(GE::IAnimator* animator) const
{
	assert(_animationSystem != nullptr);
	_animationSystem->RegisterAnimator(animator);
}

void Engine::Manager::GraphicsSystem::AnimationSystem::UnRegisterAnimator(GE::IAnimator* animator) const
{
	assert(_animationSystem != nullptr);
	_animationSystem->UnRegisterAnimator(animator);
}
