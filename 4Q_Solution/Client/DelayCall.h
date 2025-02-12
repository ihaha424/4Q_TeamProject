#pragma once

struct AsyncDelayCall
{
	void operator()(const std::function<void()>& callBack, float delaySecond) const;
};


struct DelayCall
{
	DelayCall(const std::function<void()>& callBack, float delaySecond);

	bool operator()(float deltaTime);

	std::function<void()> callBack;
	float elapsedTime;
	float delaySecond;
	bool called;
};