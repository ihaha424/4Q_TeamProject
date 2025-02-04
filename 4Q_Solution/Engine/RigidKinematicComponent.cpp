#include "pch.h"
#include "RigidKinematicComponent.h"

namespace Engine::Component
{
	RigidKinematic::RigidKinematic()
		: _rigidbody{ nullptr }
	{
	}

	void RigidKinematic::Initialize(const Modules& modules)
	{
		Component::Initialize(modules);
		static_cast<Physics::RigidKinematicComponent*>(_rigidbody)->Initialize(this);
		static_cast<Physics::RigidComponent*>(_boundBox)->Initialize(this);
	}

	void RigidKinematic::Attach()
	{
		Component::Attach();
	}
	void RigidKinematic::Update(float deltaTime)
	{
		Component::Update(deltaTime);
		static_cast<Engine::Physics::RigidKinematicComponent*>(_rigidbody)->Update(deltaTime);
		// -> Owner's Transform Update
	}
	void RigidKinematic::FixedUpdate()
	{
		Component::FixedUpdate();
	}
	void RigidKinematic::Detach()
	{
		Component::Detach();
	}
	void RigidKinematic::Finalize()
	{
		Component::Finalize();
		static_cast<Engine::Physics::RigidKinematicComponent*>(_rigidbody)->Finalize();
		static_cast<Engine::Physics::RigidComponent*>(_boundBox)->Finalize();
	}
}