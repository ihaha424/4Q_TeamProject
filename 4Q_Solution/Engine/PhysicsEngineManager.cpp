#include "pch.h"
#include "PhysicsEngineManager.h"


namespace Engine::PhysicsEngine
{
	HRESULT BoolToHRESULT(bool isSuccess)
	{
		return isSuccess ? S_OK : S_FALSE;
	}

	Manager::Manager()
		: system{ nullptr }
		, scene{ nullptr }
	{}

	void Manager::Initialize(PhysicsEngineAPI::IPhysicsSystem::PhysicsType physicsType)
	{
		constexpr Utility::ThrowIfFailed thrower;

		thrower(BoolToHRESULT(PhysicsEngineAPI::CreateSystem(&system, physicsType)));
		thrower(BoolToHRESULT(system->CreatePhysics()));
		thrower(BoolToHRESULT(PhysicsEngineAPI::CreateSystem(&system, physicsType)));

	}
	void Manager::Update(float deltaTime) const
	{
	}
	void Manager::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&scene);
		releaser(&system);
	}
}

