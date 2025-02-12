#include "pch.h"
#include "DelayCall.h"

void AsyncDelayCall::operator()(const std::function<void()>& callBack, const float delaySecond) const
{
	std::thread([=]() {
		std::this_thread::sleep_for(std::chrono::duration<float>(delaySecond));
		callBack();
	}).detach();
}

DelayCall::DelayCall(const std::function<void()>& callBack, const float delaySecond):
	callBack(callBack), elapsedTime(0), delaySecond(delaySecond), called(false)
{
}

bool DelayCall::operator()(const float deltaTime)
{
	if (called)	return false;
	elapsedTime += deltaTime;
	if (elapsedTime >= delaySecond)
	{
		called = true;
		callBack();
	}
	return true;
}
