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

		virtual void AttachUpdateSecne(IScene* scene) = 0;
		virtual void DetachUpdateSecne(IScene* scene) = 0;
		virtual IScene* GetScene(unsigned int sceneNumber) = 0;
		virtual void UpdataCameraSecne() = 0;
		virtual void 
	};

	// Engine Interface
	struct Manager : IManager
	{
		virtual void Initialize(PhysicsType physicsType = PhysicsType::Physx) = 0;
		virtual void WorldInitialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void FetchSecne(bool block = true) = 0;
		virtual void Finalize() = 0;

		virtual void* GetSystem() const = 0;
	};
}
