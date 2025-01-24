#pragma once

namespace Engine::Physics
{
	struct IScene
	{
		IScene() = default;
		IScene(const IScene& other) = default;
		IScene(IScene&& other) noexcept = default;
		IScene& operator=(const IScene& other) = default;
		IScene& operator=(IScene&& other) noexcept = default;
		virtual ~IScene() = default;
	};

	struct Scene : IScene
	{
		virtual void Initialize(const SceneDesc& sceneDescription, const char* name = nullptr) = 0;
		virtual void Update(float deltaTime) const = 0;
		virtual void Finalize() = 0;
	};
}
