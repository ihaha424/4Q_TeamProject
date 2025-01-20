#include "pch.h"
#include "DSHNegative.h"

Engine::DSHInput::Modifier::Negative::Negative():
	_negative(nullptr)
{
}

void Engine::DSHInput::Modifier::Negative::Setup(DSH::Input::Modifier::INegative* negative)
{
	negative->AddRef();
	_negative = negative;
}

void Engine::DSHInput::Modifier::Negative::Finalize()
{
	Utility::SafeRelease()(&_negative);
}
