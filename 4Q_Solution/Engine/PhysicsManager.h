#pragma once


namespace Engine::Physics
{
	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;
	};

	struct Manager : IManager
	{
		virtual void Initialize(PhysicsEngineAPI::IPhysicsSystem::PhysicsType physicsType = PhysicsEngineAPI::IPhysicsSystem::PhysicsType::Physx) = 0;
		virtual void Update(float deltaTime) const = 0;
		virtual void Finalize() = 0;
	};
}
