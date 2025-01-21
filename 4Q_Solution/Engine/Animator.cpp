#include "pch.h"
#include "Animator.h"

Engine::Component::Animator::Animator()
	: _animator(nullptr)
{
}

void Engine::Component::Animator::ChangeAnimation(const char* animation) const
{
	_animator->ChangeAnimation(animation);
}

void Engine::Component::Animator::ChangeAnimation(const char* animation, const unsigned int ID) const
{
	_animator->ChangeAnimation(animation, ID);
}

bool Engine::Component::Animator::IsLastFrame(float interval) const
{
	return _animator->IsLastFrame(interval);
}

void Engine::Component::Animator::SetUpSplitBone(const unsigned int maxSplit) const
{
	_animator->SetUpSplitBone(maxSplit);
}

void Engine::Component::Animator::SplitBone(const unsigned int ID, const char* boneName) const
{
	_animator->SplitBone(ID, boneName);
}
