#pragma once

namespace Engine::UI
{
	class UserInterface
	{
	public:
		explicit UserInterface(Math::Rect* rect);
		UserInterface(const UserInterface& other) = default;
		UserInterface(UserInterface&& other) noexcept = default;
		UserInterface& operator=(const UserInterface& other) = default;
		UserInterface& operator=(UserInterface&& other) noexcept = default;
		virtual ~UserInterface() = default;


        virtual void Initialize();
		virtual void Attach();
		virtual void Update(float deltaGameTime);
		virtual void FixedUpdate();
		virtual void Detach();
		virtual void Finalize();

        void SetPadding(const Math::Padding& padding);
        void SetMargin(const Math::Margin& margin);

	private:
		void UpdateRect();
		void UpdateMyRect();
		void UpdateChildRect();

        Math::Padding _padding;
        Math::Margin _margin;

		Math::Rect* _parentRect;

	protected:
        Math::Rect _myRect;
		Math::Rect _childRect;
	};
}