#pragma once

// #include <DirectXMath.h> // TODO: Requires Math library

namespace Engine::Input
{
	union Value;
}


namespace Engine::Math
{
	struct Vector3
	{
		Vector3(float x, float y, float z);

		Vector3& operator+= (const Vector3& rhs) noexcept;
		Vector3 operator* (float scalar) const noexcept;

		float x;
		float y;
		float z;

		// Constants
		static const Vector3 Zero;
		static const Vector3 One;

		// Convert
		Vector3(const Input::Value& value) noexcept;
	};
}
