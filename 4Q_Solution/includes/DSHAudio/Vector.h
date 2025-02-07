#pragma once

namespace DSH::Audio
{
	struct Vector : FMOD_VECTOR
	{
		Vector();
		Vector(float x, float y, float z);
	};
}
