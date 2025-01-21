#pragma once

namespace Engine::Component
{
	class Component
	{
	public:
		Component() = default;
		Component(const Component& other) = default;
		Component(Component&& other) noexcept = default;
		Component& operator=(const Component& other) = default;
		Component& operator=(Component&& other) noexcept = default;
		virtual ~Component() = default;

		virtual void Initialize();
		virtual void Attach();
		virtual void Update(float deltaTime);
		virtual void FixedUpdate();
		virtual void Detach();
		virtual void Finalize();

	protected:
		// TODO: Owner
	};
}

