#pragma once

namespace Engine::UI
{
	class UserInterface
	{
    public:
        explicit UserInterface(Math::Rect* rect);

        void Initialize();
		void Attach();
		void Update(float deltaGameTime);
		void FixedUpdate();
		void Detach();
		void Finalize() const;

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