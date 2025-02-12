#include "pch.h"
#include "DelayCall.h"

void AsyncDelayCall::operator()(const std::function<void()>& callBack, const float delaySecond) const
{
	std::thread([=]() {
		std::this_thread::sleep_for(std::chrono::duration<float>(delaySecond));
		callBack();
	}).detach();
}
