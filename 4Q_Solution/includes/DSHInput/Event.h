#pragma once

namespace DSH::Input::Trigger
{
	enum class Event : unsigned char
	{
		Triggered = 4,
		Started = 2,
		Ongoing = 0,
		Completed = 1,
		Canceled = 3
	};
}
