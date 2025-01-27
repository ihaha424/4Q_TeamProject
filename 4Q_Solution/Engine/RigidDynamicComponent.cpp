#include "pch.h"
#include "RigidDynamicComponent.h"

namespace Engine::Component
{
	RigidDynamicComponent::RigidDynamicComponent()
		: _rigidComponent{ nullptr }
		, _physicsManager{ nullptr }
	{
	}
	void RigidDynamicComponent::Setup(Modules modules)
	{
		Component::Setup(modules);
		_physicsManager = modules.physicsManager;
	}
	void RigidDynamicComponent::Initialize()
	{
		Component::Initialize();
	}
	void RigidDynamicComponent::Attach()
	{
		Component::Attach();
	}
	void RigidDynamicComponent::Update(float deltaTime)
	{
		Component::Update(deltaTime);
		// -> Owner's Transform Update
	}
	void RigidDynamicComponent::FixedUpdate()
	{
		Component::FixedUpdate();
	}
	void RigidDynamicComponent::Detach()
	{
		Component::Detach();
	}
	void RigidDynamicComponent::Finalize()
	{
		Component::Finalize();
	}
}