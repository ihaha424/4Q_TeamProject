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
	void PostAttach() override;

private:
	std::filesystem::path _meshPath;

	Engine::Component::Movement* _movement;
	Engine::Component::Camera* _camera;
	Engine::Component::SkeletalMesh* _skeletalMesh;
	Engine::Component::Animator* _animator;
	Engine::Math::Matrix _worldMatrix;

	Engine::Math::Matrix _cameraParentMatrix;
	Engine::Math::Vector3 _cameraRotation;
};