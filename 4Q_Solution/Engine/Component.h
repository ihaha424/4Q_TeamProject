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

		void Dispose();
		[[nodiscard]] bool IsDisposed() const;

		virtual void Initialize(const Modules& modules);
		virtual void Attach();
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);
		virtual void FixedUpdate();
		virtual void Detach();
		virtual void Finalize();

		void SetOwner(Object* owner);
		[[nodiscard]] Object* GetOwner() const;
		template <typename T> requires std::derived_from<T, Object>
		[[nodiscard]] T* GetOwner() const
		{
			return dynamic_cast<T*>(_owner);
		}

	protected:
		bool _isDispose;

		Object* _owner;
	};
}

