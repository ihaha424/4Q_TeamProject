#pragma once

namespace Engine::Math
{
	struct Vector3
	{
		Vector3(float x, float y, float z);

		float x;
		float y;
		float z;

		// Constants
		static const Vector3 Zero;

		// Convert
		Vector3(DSH::Input::Value value) noexcept;
	};
}
