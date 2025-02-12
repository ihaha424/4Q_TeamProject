#pragma once

namespace Engine
{
    namespace UI::Panel
    {
        class Anchor;
    }

	class Canvas
	{
    public:
        explicit Canvas(const Math::Size& viewportSize);

        void Initialize();
        void Attach();
        void Update(float deltaGameTime) const;
		void FixedUpdate() const;
		void Detach();
        void Finalize() const;

        [[nodiscard]] UI::Panel::Anchor GetRootPanel() const;

    protected:
        UI::Panel::Anchor* _rootPanel;
	};
}