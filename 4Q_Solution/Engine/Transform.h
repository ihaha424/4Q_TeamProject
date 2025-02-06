#pragma once

namespace Engine
{
	struct Transform
	{
		Transform();
		Transform(Math::Vector3 position, Math::Quaternion rotation, Math::Vector3 scale);

		void Translate(Math::Vector3 translation);
		Math::Matrix GetMatrix();

		Math::Vector3 position;
		Math::Quaternion rotation;
		Math::Vector3 scale;
	};
}
