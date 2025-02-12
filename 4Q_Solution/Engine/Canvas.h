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

		void Initialize(const Modules& modules);
		void Attach();
		void Update(float deltaGameTime);
		void FixedUpdate();
		void Detach();
		void Finalize();

		[[nodiscard]] UI::Panel::Anchor* GetRootPanel();

	protected:
		Math::Rect _rect;
		UI::Panel::Anchor _rootPanel;
	};
}