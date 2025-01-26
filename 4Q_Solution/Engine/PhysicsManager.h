#pragma once

namespace Engine::Physics
{
	// Client Interface
	struct IManager
		: public ICreate
		, public IUpdate
		, public IFactory
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

	};

	// Engine Interface
	struct Manager : IManager
	{
		virtual void Initialize(PhysicsType physicsType = PhysicsType::Physx) = 0;
		virtual void WorldInitialize() = 0;
		virtual void Update(float deltaTime) const = 0;
		virtual void Finalize() = 0;

		virtual void* GetSystem() = 0;
	};
}
