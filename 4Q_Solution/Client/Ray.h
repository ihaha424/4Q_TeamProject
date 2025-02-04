#pragma once
//#include "RayState.h"

class Ray : public Engine::Object
{
public:
	Ray(std::filesystem::path&& meshPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
protected:
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	void PostUpdate(float deltaTime) override;

private:
	Engine::Math::Matrix _worldMatrix;
	std::filesystem::path _meshPath;

	Engine::Component::SkeletalMesh* _skeletalMesh;
	Engine::Component::Animator* _animator;
	Engine::Component::Movement* _movement;
	Engine::Component::FiniteStateMachine* _animationFSM;
};