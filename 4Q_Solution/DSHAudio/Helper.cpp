#include "pch.h"
#include "Helper.h"

HRESULT DSH::Audio::Helper::FmodResultToHResult::operator()(const FMOD_RESULT result) const
{
	return result == FMOD_OK ? S_OK : E_FAIL;
}

void DSH::Audio::Helper::ConditionSequence::operator()(FMOD_RESULT(FMOD::ChannelControl::* function)(bool* result),
                                                       FMOD::ChannelControl* control)
{
	result = (control->*function)(&state);
}

HRESULT DSH::Audio::Helper::ConditionSequence::operator()(const bool requiredState,
	FMOD_RESULT(FMOD::ChannelControl::* function)(bool state), FMOD::ChannelControl* control) const
{
	if (result != FMOD_OK) return E_FAIL;
	if (state == requiredState) return S_OK;
	return FmodResultToHResult()((control->*function)(requiredState));
}
