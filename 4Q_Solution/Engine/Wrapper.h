#pragma once

namespace Engine::UI::Wrapper
{
	class Wrapper : public UserInterface
	{
	public:
		explicit Wrapper(Math::Rect* rect);
		~Wrapper() override;

		void Initialize() override;
		void Attach() override;
		void Update(float deltaGameTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

        void SetChild(UserInterface* child);

        template <typename T, typename... Args>
		T* CreateChild(Args&&... args)
		{
			T* child = new T(std::forward<Args>(args)...);
			SetChild(child);
			return child;
		}

    protected:
		UserInterface* _child;
	};
}
