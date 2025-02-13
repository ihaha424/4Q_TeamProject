#pragma once

class NPC : public Engine::Object
{
public:
	NPC(std::filesystem::path meshPath, Engine::Math::Matrix matrix);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;

protected:
	std::filesystem::path _meshPath;
	Engine::Math::Matrix _worldMatrix;

	Engine::Component::SkeletalMesh* _skeletalMesh;
	Engine::Component::Animator* _animator;
};