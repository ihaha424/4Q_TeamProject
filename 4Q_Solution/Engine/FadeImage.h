#pragma once

namespace Engine::UI::Wrapper
{
	class FadeImage : public Image
	{
	public:
		using Event = std::function<void()>;

	private:
		enum class State
		{
			Idle,
			FadeIn,
			FadeOut
		};

	public:
		FadeImage(Math::Rect* rect, const std::filesystem::path& path, float duration);

		void FadeIn();
		void FadeOut();

		void Update(float deltaGameTime) override;

		void SetDuration(float duration);
		void SetOpacity(float opacity);

		void BindOnFadeInEnd(Event event);
		void BindOnFadeOutEnd(Event event);

		void Reset();

	protected:
		void UpdateFade(float deltaTime);

	private:
		float _opacity;
		float _duration;
		float _elapsedTime;
		State _state;
		Event _onFadeInEnd;
		Event _onFadeOutEnd;
	};
}