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
		virtual ~Canvas() = default;
		explicit Canvas(const Math::Size& viewportSize);

		virtual void Initialize(const Modules& modules);
		virtual void Attach();
		virtual void Update(float deltaGameTime);
		virtual void FixedUpdate();
		virtual void Detach();
		virtual void Finalize();

		virtual void Action();

		[[nodiscard]] UI::Panel::Anchor* GetRootPanel();

	protected:
		Math::Rect _rect;
		UI::Panel::Anchor _rootPanel;
	};
}