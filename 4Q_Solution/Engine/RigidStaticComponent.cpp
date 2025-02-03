#include "pch.h"
#include "RigidStaticComponent.h"

namespace Engine::Component
{
	RigidStatic::RigidStatic()
		: _rigidbody{ nullptr }
	{
	}

	void RigidStatic::Initialize(const Modules& modules)
	{
		Component::Initialize(modules);
		static_cast<Physics::RigidStaticComponent*>(_rigidbody)->Initialize();
		static_cast<Physics::RigidComponent*>(_boundBox)->Initialize();
	}

	void RigidStatic::Attach()
	{
		Component::Attach();
	}
	void RigidStatic::Update(float deltaTime)
	{
		Component::Update(deltaTime);
		static_cast<Engine::Physics::RigidStaticComponent*>(_rigidbody)->Update(deltaTime);

	}
	void RigidStatic::FixedUpdate()
	{
		Component::FixedUpdate();
	}
	void RigidStatic::Detach()
	{
		Component::Detach();
	}
	void RigidStatic::Finalize()
	{
		Component::Finalize();
		static_cast<Engine::Physics::RigidStaticComponent*>(_rigidbody)->Finalize();
		static_cast<Engine::Physics::RigidComponent*>(_boundBox)->Finalize();
	}
}