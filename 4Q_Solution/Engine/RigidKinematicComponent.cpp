#include "pch.h"
#include "RigidKinematicComponent.h"

namespace Engine::Component
{
	RigidKinematicComponent::RigidKinematicComponent()
		: _rigidComponent{ nullptr }
		, _physicsManager{ nullptr }
	{
	}
	void RigidKinematicComponent::Setup(Modules modules)
	{
		Component::Setup(modules);
		_physicsManager = modules.physicsManager;
	}
	void RigidKinematicComponent::Initialize()
	{
		Component::Initialize();
		static_cast<Physics::RigidKinematicComponent*>(_rigidComponent)->Initialize();

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