#include "pch.h"
#include "FadeImage.h"

Engine::UI::Wrapper::FadeImage::FadeImage(Math::Rect* rect, const std::filesystem::path& path, const float duration)
	: Image(rect, path), _opacity(0.f), _duration(duration), _elapsedTime(0), _state(State::Idle) 
{
}

void Engine::UI::Wrapper::FadeImage::FadeIn()
{
	_state = State::FadeIn;
}

void Engine::UI::Wrapper::FadeImage::FadeOut()
{
	_state = State::FadeOut;
}

void Engine::UI::Wrapper::FadeImage::Update(const float deltaGameTime)
{
	UpdateFade(deltaGameTime);
    _sprite.SetAlpha(_opacity);
	Image::Update(deltaGameTime);
}

void Engine::UI::Wrapper::FadeImage::SetDuration(const float duration)
{
	_duration = duration;
}

void Engine::UI::Wrapper::FadeImage::SetOpacity(const float opacity)
{
	_opacity = opacity;
}

void Engine::UI::Wrapper::FadeImage::BindOnFadeInEnd(Event event)
{
	_onFadeInEnd = std::move(event);
}

void Engine::UI::Wrapper::FadeImage::BindOnFadeOutEnd(Event event)
{
	_onFadeOutEnd = std::move(event);
}

void Engine::UI::Wrapper::FadeImage::Reset()
{
	_opacity = 0.0f;
	_elapsedTime = 0.0f;
	_state = State::Idle;
}

void Engine::UI::Wrapper::FadeImage::UpdateFade(const float deltaTime)
{
    if (_state == State::Idle) return;
    float time = 0;
    if (_state == State::FadeIn)
    {
        _elapsedTime += deltaTime;
        time = (std::min)(_elapsedTime / _duration, 1.f);
        if (time == 1.f)
        {
            _state = State::Idle;
            if (_onFadeInEnd) _onFadeInEnd();
        }
    }
    else if (_state == State::FadeOut)
    {
        _elapsedTime -= deltaTime;
        time = (std::max)(_elapsedTime / _duration, 0.f);
        if (time == 0.f)
        {
            _state = State::Idle;
            if (_onFadeOutEnd) _onFadeOutEnd();
        }
    }
    _opacity = std::lerp(0.f, 1.f, time);
}
