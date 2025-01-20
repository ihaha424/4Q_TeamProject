#pragma once

namespace Engine::Input::Modifier
{
	struct INegative
	{
		INegative() = default;
		INegative(const INegative& other) = default;
		INegative(INegative&& other) noexcept = default;
		INegative& operator=(const INegative& other) = default;
		INegative& operator=(INegative&& other) noexcept = default;
		virtual ~INegative() = default;
	};

	struct Negative : INegative
	{
		virtual void Finalize() = 0;
	};
}