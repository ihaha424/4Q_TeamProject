#pragma once

namespace Engine::Physics
{
	// Engine Interface
	struct Object
	{
		Object() = default;
		Object(const Object& other) = default;
		Object(Object&& other) noexcept = default;
		Object& operator=(const Object& other) = default;
		Object& operator=(Object&& other) noexcept = default;
		virtual ~Object() = default;

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) const = 0;
		virtual void Finalize() = 0;
	};
}
