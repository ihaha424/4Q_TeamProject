#pragma once

namespace Engine::Math
{
	struct Size : SIZE
	{
		Size() noexcept = default;

		Size(long cx, long cy) noexcept;

		Size(const SIZE& size) noexcept;
		Size& operator=(const SIZE& size) noexcept;
	};
}
