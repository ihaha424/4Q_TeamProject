#pragma once

namespace Engine::UI::Wrapper
{
	class Button : public Wrapper
	{
    public:
        using Event = std::function<void()>;

        explicit Button(Math::Rect* rect);

        void Update(float deltaTime) override;

        void BindOnHoverBegin(const Event& event);
        void BindOnHoverEnd(const Event& event);
        void BindOnClick(const Event& event);

        void HoverCheck();
        void ClickCheck() const;

    private:
        Event _onHoverBegin;
        Event _onHoverEnd;
        bool _isHover;

        Event _onClick;
	};
}
