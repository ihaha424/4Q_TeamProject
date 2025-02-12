#pragma once

struct AsyncDelayCall
{
	void operator()(const std::function<void()>& callBack, float delaySecond) const;
};