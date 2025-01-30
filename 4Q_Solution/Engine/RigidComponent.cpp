#include "pch.h"
#include "RigidComponent.h"

namespace Engine::Component
{
	Rigid::Rigid()
		: _rigidbody{ nullptr }
	{}

	void Rigid::Initialize(const Modules& modules)
	{
		Component::Initialize(modules);
		static_cast<Physics::RigidComponent*>(_rigidbody)->Initialize();
		static_cast<Physics::RigidComponent*>(_boundBox)->Initialize();
	}

	void Rigid::Attach()
	{
		Component::Attach();
	}
	void Rigid::Update(float deltaTime)
	{
		Component::Update(deltaTime);
		static_cast<Engine::Physics::RigidComponent*>(_rigidbody)->Update(deltaTime);
	}
	void Rigid::FixedUpdate()
	{
		Component::FixedUpdate();
	}
	void Rigid::Detach()
	{
		Component::Detach();
	}
	void Rigid::Finalize()
	{
		Component::Finalize();
	}
}