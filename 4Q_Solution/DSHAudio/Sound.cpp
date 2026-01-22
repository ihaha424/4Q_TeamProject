#include "pch.h"
#include "Sound.h"

#include "Helper.h"

DSH::Audio::Sound::Sound(FMOD::System* system, FMOD::ChannelGroup* group, const std::filesystem::path& path,
                         const bool isLoop):
	_referenceCount(1), _system(system), _channel(nullptr), _sound(nullptr), _group(group), _rate(0)
{
	_system->createSound(path.string().c_str(), isLoop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, nullptr, &_sound);
	_system->getSoftwareFormat(&_rate, nullptr, nullptr);
}

DSH::Audio::Sound::~Sound()
{
	[[maybe_unused]] auto result = Stop();
	_sound->release();
	_sound = nullptr;
}

HRESULT DSH::Audio::Sound::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_ISound &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Audio::Sound::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Audio::Sound::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

HRESULT DSH::Audio::Sound::Play()
{
	return Helper::FmodResultToHResult()(_system->playSound(_sound, _group, false, &_channel));
}

HRESULT DSH::Audio::Sound::Stop()
{
	if (_channel == nullptr) return S_OK;
	HRESULT result = Helper::FmodResultToHResult()(_channel->removeFadePoints(0, _rate));
	result = Helper::FmodResultToHResult()(_channel->stop());
	_channel = nullptr;
	return result;
}

bool DSH::Audio::Sound::IsPlaying() const
{
	if (_channel == nullptr) return false;
	bool isPlaying = false;
	_channel->isPlaying(&isPlaying);
	return isPlaying;
}

HRESULT DSH::Audio::Sound::Pause()
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getPaused, _channel);
	return sequence(true, &FMOD::ChannelControl::setPaused, _channel);
}

HRESULT DSH::Audio::Sound::Resume()
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getPaused, _channel);
	return sequence(false, &FMOD::ChannelControl::setPaused, _channel);
}

bool DSH::Audio::Sound::IsPaused() const
{
	if (_channel == nullptr) return false;
	bool isPaused = false;
	_channel->getPaused(&isPaused);
	return isPaused;
}

HRESULT DSH::Audio::Sound::SetVolume(const float volume)
{
	return Helper::FmodResultToHResult()(_channel->setVolume(volume));
}

float DSH::Audio::Sound::GetVolume() const
{
	if (_channel == nullptr) return 0.0f;
	float volume = 0.0f;
	_channel->getVolume(&volume);
	return volume;
}

HRESULT DSH::Audio::Sound::Mute()
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getMute, _channel);
	return sequence(true, &FMOD::ChannelControl::setMute, _channel);
}

HRESULT DSH::Audio::Sound::Unmute()
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getMute, _channel);
	return sequence(false, &FMOD::ChannelControl::setMute, _channel);
}

bool DSH::Audio::Sound::IsMuted() const
{
	if (_channel == nullptr) return false;
	bool isMuted = false;
	_channel->getMute(&isMuted);
	return isMuted;
}

HRESULT DSH::Audio::Sound::FadeIn(const float fadeTime)
{
	if (!IsPlaying()) return E_ABORT;
	if (fadeTime <= 0.f) return E_INVALIDARG;
	const unsigned long long start = GetDspClock();
	const unsigned long long end = start + GetSampleRateTime(fadeTime);
	_channel->removeFadePoints(start, end);
	_channel->addFadePoint(start, 0.f);
	_channel->addFadePoint(end, 1.f);
	return S_OK;
}

HRESULT DSH::Audio::Sound::FadeOut(const float fadeTime)
{
	if (!IsPlaying()) return E_ABORT;
	if (fadeTime <= 0.f) return E_INVALIDARG;
	const unsigned long long start = GetDspClock();
	const unsigned long long end = start + GetSampleRateTime(fadeTime);
	_channel->removeFadePoints(start, end);
	_channel->addFadePoint(start, 1.f);
	_channel->addFadePoint(end, 0.f);
	return S_OK;
}

HRESULT DSH::Audio::Sound::SetDelay(const float delayTime)
{
	if (_channel == nullptr) return E_ABORT;
	return Helper::FmodResultToHResult()(_channel->setDelay(GetDspClock() + GetSampleRateTime(delayTime), 0, false));
}

float DSH::Audio::Sound::GetLength() const
{
	if (_channel == nullptr) return 0.f;
	unsigned int length;
	_sound->getLength(&length, FMOD_TIMEUNIT_MS);
	return static_cast<float>(length) / 1000.f;
}

unsigned long long DSH::Audio::Sound::GetDspClock() const
{
	unsigned long long dspClock;
	_channel->getDSPClock(nullptr, &dspClock);
	return dspClock;
}

unsigned long long DSH::Audio::Sound::GetSampleRateTime(const float time) const
{
	return static_cast<unsigned long long>(time * static_cast<double>(_rate));
}

unsigned int DSH::Audio::Sound::GetPosition() const
{
	unsigned int position;
	_channel->getPosition(&position, FMOD_TIMEUNIT_PCM);
	return position;
}
