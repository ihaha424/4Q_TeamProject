#pragma once

namespace Engine::Math
{
	struct Vector4
	{
		Vector4(float x, float y, float z);

		Vector4& operator+= (const Vector4& rhs) noexcept;
		Vector4 operator* (float scalar) const noexcept;

		float x;
		float y;
		float z;

		// Constants
		static const Vector4 Zero;
		static const Vector4 One;

	};
}