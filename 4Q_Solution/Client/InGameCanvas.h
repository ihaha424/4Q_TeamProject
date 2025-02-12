#pragma once

namespace Engine::UI::Wrapper
{
	class FadeImage;
}

class InGameCanvas final : public Engine::Canvas
{
public:
	InGameCanvas();
	explicit InGameCanvas(const Engine::Math::Size& viewportSize);

	void Initialize(const Engine::Modules& modules) override;
	void Attach() override;


private:
	Engine::UI::Wrapper::FadeImage* _fadeMask;
};