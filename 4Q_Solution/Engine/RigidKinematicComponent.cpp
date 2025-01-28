#include "pch.h"
#include "RigidKinematicComponent.h"

namespace Engine::Component
{
	RigidKinematicComponent::RigidKinematicComponent()
		: _rigidComponent{ nullptr }
		, _physicsManager{ nullptr }
	{
	}

	void RigidKinematicComponent::Initialize(const Modules& modules)
	{
		Component::Initialize(modules);
		_physicsManager = modules.physicsManager;
	}

	void RigidKinematicComponent::Attach()
	{
		Component::Attach();
	}
	void RigidKinematicComponent::Update(float deltaTime)
	{
		Component::Update(deltaTime);
		// -> Owner's Transform Update
	}
	void RigidKinematicComponent::FixedUpdate()
	{
		Component::FixedUpdate();
	}
	void RigidKinematicComponent::Detach()
	{
		Component::Detach();
	}
	void RigidKinematicComponent::Finalize()
	{
		Component::Finalize();
	}
}