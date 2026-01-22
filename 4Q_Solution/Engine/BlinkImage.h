#pragma once

namespace Engine::UI::Wrapper
{
	class BlinkImage : public FadeImage
	{
	public:
		BlinkImage(Math::Rect* rect, const std::filesystem::path& path, float blinkTime);

		void Initialize(const Modules& modules) override;
	};
}