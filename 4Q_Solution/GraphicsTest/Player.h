#pragma once

class Player : public Engine::Object
{
public:
	Player(std::filesystem::path&& meshPath, std::filesystem::path&& fontPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
protected:
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	void PostAttach() override;
	void PostUpdate(float deltaTime) override;

private:
	std::filesystem::path _meshPath;
	std::filesystem::path _fontPath;

	Engine::Component::Movement* _movement;
	Engine::Component::Camera* _camera;
	Engine::Component::SkeletalMesh* _skeletalMesh;
	Engine::Component::Animator* _animator;
	Engine::Math::Matrix _worldMatrix;
	Engine::Component::TextRenderer* _textRenderer;

	Engine::Math::Vector3 _camRotation;
};