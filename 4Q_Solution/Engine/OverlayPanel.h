#pragma once

namespace Engine::UI::Panel
{
	class Overlay : public UserInterface
	{
	public:
		class Child;

	private:
		template <typename T>
		using ChildPair = std::pair<Child*, T*>;

	public:
		explicit Overlay(Math::Rect* rect);
		~Overlay() override;

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaGameTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

		void AddChild(Child* child);

		template <typename T, typename... Args>
			requires std::derived_from<T, UserInterface> && std::constructible_from<T, Math::Rect*, Args...>
		ChildPair<T> CreateChild(Args&&... args)
		{
			T* control = new T(&_childRect, std::forward<Args>(args)...);
			Child* child = new Child(control);
			AddChild(child);
			return { child, control };
		}

	private:
		std::vector<Child*> _children;

	public:
		class Child
		{
		public:
			explicit Child(UserInterface* child);

			void Initialize(const Modules& modules) const;
			void Attach() const;
			void Update(float deltaGameTime) const;
			void FixedUpdate() const;
			void Detach() const;
			void Finalize() const;

		private:
			UserInterface* _child;
		};
	};
}