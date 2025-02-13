#pragma once

namespace Engine::UI::Panel
{
	class Anchor : public UserInterface
	{
	public:
		class Child;

	private:
		template <typename T>
		using ChildPair = std::pair<Child*, T*>;

	public:
		explicit Anchor(Math::Rect* rect);
		~Anchor() override;

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
            enum class HorizontalAnchoring : unsigned char;
            enum class VerticalAnchoring : unsigned char;
            explicit Child(UserInterface* child);

            void Initialize(const Modules& modules) const;
			void Attach() const;
			void Update(float deltaGameTime) const;
			void FixedUpdate() const;
			void Detach() const;
			void Finalize() const;

            [[nodiscard]] std::pair<HorizontalAnchoring, VerticalAnchoring> GetAnchoring() const;
            void SetAnchoring(HorizontalAnchoring horizontal, VerticalAnchoring vertical);

        private:
            UserInterface* _child;
            HorizontalAnchoring _horizontal;
            VerticalAnchoring _vertical;

        public:
			enum class HorizontalAnchoring : unsigned char
            {
                Left,
                Center,
                Right
            };
			enum class VerticalAnchoring : unsigned char
            {
                Top,
                Center,
                Bottom
            };
        };
	};
}