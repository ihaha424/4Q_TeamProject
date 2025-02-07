#pragma once

namespace DSH::Audio::Helper
{
	struct FmodResultToHResult
	{
		HRESULT operator()(const FMOD_RESULT result) const;
	};

	struct ConditionSequence
	{
		void operator()(FMOD_RESULT(FMOD::ChannelControl::* function)(bool* result), FMOD::ChannelControl* control);

		HRESULT operator()(const bool requiredState, FMOD_RESULT(FMOD::ChannelControl::* function)(bool state), FMOD::ChannelControl* control) const;

		FMOD_RESULT result;
		bool state;
	};
}