#pragma once


class PhysicsObjectExample
	: public Engine::Object
{
public:
	PhysicsObjectExample();

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PreUpdate(float deltaTime) override;
	void PostUpdate(float deltaTime) override;
	void PreFixedUpdate() override;
	void PostFixedUpdate() override;
	
	void SceneQueryExample();

private:
	Engine::Component::Rigid*			_rigid;
	Engine::Component::RigidStatic*		_rigidStatic;
	Engine::Component::RigidDynamic*	_rigidDynamic;
	Engine::Component::RigidKinematic*	_rigidKinematic;
};

