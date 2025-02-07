#include "pch.h"
#include "System.h"

#include "Helper.h"
#include "Sound.h"

DSH::Audio::System::System():
_referenceCount(1)
{
    // TODO: Use FMOD_RESULT
	System_Create(&_system);
	int channelNumber;
	_system->getSoftwareChannels(&channelNumber);
	_system->init(channelNumber, FMOD_INIT_NORMAL, nullptr);
	_system->createChannelGroup("Background", &_channelGroups[ChannelGroupType::Background]);
	_system->createChannelGroup("Effect", &_channelGroups[ChannelGroupType::Effect]);
	_system->getMasterChannelGroup(&_masterGroup);
	for (const auto& group : _channelGroups | std::views::values)
	{
		_masterGroup->addGroup(group);
	}
}

DSH::Audio::System::~System()
{
    _masterGroup->release();
    for (const auto& group : _channelGroups | std::views::values)
    {
        group->release();
    }
    _system->close();
    _system->release();
}

HRESULT DSH::Audio::System::QueryInterface(const IID& riid, void** ppvObject)
{
    if (ppvObject == nullptr) return E_INVALIDARG;
    if (riid != IID_ISystem &&
        riid != IID_IUnknown) return E_NOINTERFACE;
    *ppvObject = this;
    return S_OK;
}

ULONG DSH::Audio::System::AddRef()
{
    return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Audio::System::Release()
{
    const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
    if (newRefCount == 0) delete this;
    return newRefCount;
}

void DSH::Audio::System::Update()
{
    _system->update();
}

HRESULT DSH::Audio::System::CreateSound(const std::filesystem::path& path, const ChannelGroupType group, const bool isLoop,
	ISound** ppSound)
{
	if (ppSound == nullptr) return E_INVALIDARG;
	Sound* pTickTimer = new Sound(_system, _channelGroups[group], path, isLoop);
	if (pTickTimer == nullptr) return E_OUTOFMEMORY;
	*ppSound = pTickTimer;
	return S_OK;
}

HRESULT DSH::Audio::System::Pause()
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getPaused, _masterGroup);
	return sequence(true, &FMOD::ChannelControl::setPaused, _masterGroup);
}

HRESULT DSH::Audio::System::Pause(const ChannelGroupType group)
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getPaused, _channelGroups[group]);
	return sequence(true, &FMOD::ChannelControl::setPaused, _channelGroups[group]);
}

HRESULT DSH::Audio::System::Resume()
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getPaused, _masterGroup);
	return sequence(false, &FMOD::ChannelControl::setPaused, _masterGroup);
}

HRESULT DSH::Audio::System::Resume(const ChannelGroupType group)
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getPaused, _channelGroups[group]);
	return sequence(false, &FMOD::ChannelControl::setPaused, _channelGroups[group]);
}

HRESULT DSH::Audio::System::Stop()
{
	return Helper::FmodResultToHResult()(_masterGroup->stop());
}

HRESULT DSH::Audio::System::Stop(const ChannelGroupType group)
{
	return Helper::FmodResultToHResult()(_channelGroups[group]->stop());
}

HRESULT DSH::Audio::System::SetVolume(const float volume)
{
	return Helper::FmodResultToHResult()(_masterGroup->setVolume(volume));
}

HRESULT DSH::Audio::System::SetVolume(const ChannelGroupType group, const float volume)
{
	return Helper::FmodResultToHResult()(_channelGroups[group]->setVolume(volume));
}

HRESULT DSH::Audio::System::Mute()
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getMute, _masterGroup);
	return sequence(true, &FMOD::ChannelControl::setMute, _masterGroup);
}

HRESULT DSH::Audio::System::Mute(const ChannelGroupType group)
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getMute, _channelGroups[group]);
	return sequence(true, &FMOD::ChannelControl::setMute, _channelGroups[group]);
}

HRESULT DSH::Audio::System::Unmute()
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getMute, _masterGroup);
	return sequence(false, &FMOD::ChannelControl::setMute, _masterGroup);
}

HRESULT DSH::Audio::System::Unmute(const ChannelGroupType group)
{
	Helper::ConditionSequence sequence;
	sequence(&FMOD::ChannelControl::getMute, _channelGroups[group]);
	return sequence(false, &FMOD::ChannelControl::setMute, _channelGroups[group]);
}
