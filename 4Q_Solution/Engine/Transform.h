#pragma once

namespace Engine
{
	struct Transform
	{
		Transform();

		void Translate(Math::Vector3 translation);

		Math::Vector3 position;
		Math::Quaternion rotation;
		Math::Vector3 scale;
	};
}
