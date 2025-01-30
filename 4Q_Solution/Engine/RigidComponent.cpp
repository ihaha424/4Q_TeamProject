#include "pch.h"
#include "RigidComponent.h"

namespace Engine::Component
{
	RigidComponent::RigidComponent()
		: _rigidComponent{ nullptr }
		, _physicsManager{ nullptr }
	{}

	void RigidComponent::Initialize(const Modules& modules)
	{
		Component::Initialize(modules);
		static_cast<Physics::RigidComponent*>(_rigidComponent)->Initialize();
	}

	void RigidComponent::Attach()
	{
		Component::Attach();
	}
	void RigidComponent::Update(float deltaTime)
	{
		Component::Update(deltaTime);
	}
	void RigidComponent::FixedUpdate()
	{
		Component::FixedUpdate();
	}
	void RigidComponent::Detach()
	{
		Component::Detach();
	}
	void RigidComponent::Finalize()
	{
		Component::Finalize();
	}
}