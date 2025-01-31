#include "pch.h"
#include "RigidDynamicComponent.h"

namespace Engine::Component
{
	RigidDynamic::RigidDynamic()
		: _rigidbody{ nullptr }
	{
	}

	void RigidDynamic::Initialize(const Modules& modules)
	{
		Component::Initialize(modules);
		static_cast<Physics::RigidDynamicComponent*>(_rigidbody)->Initialize();
		static_cast<Physics::RigidComponent*>(_boundBox)->Initialize();
	}

	void RigidDynamic::Attach()
	{
		Component::Attach();
	}
	void RigidDynamic::Update(float deltaTime)
	{
		Component::Update(deltaTime);
		//TODO:: Component를 어떻게 할지 몰라서 임시로
		static_cast<Engine::Physics::RigidDynamicComponent*>(_rigidbody)->Update(deltaTime);
		// -> Owner's Transform Update
	}
	void RigidDynamic::FixedUpdate()
	{
		Component::FixedUpdate();
	}
	void RigidDynamic::Detach()
	{
		Component::Detach();
	}
	void RigidDynamic::Finalize()
	{
		Component::Finalize();
	}
}