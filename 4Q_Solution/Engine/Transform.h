#pragma once

namespace Engine
{
	struct Transform
	{
		Transform();
		Transform(Math::Vector3 position, Math::Quaternion rotation, Math::Vector3 scale);

		void Translate(Math::Vector3 translation);
		Math::Matrix GetMatrix();

		Math::Vector3 GetForward() const;
		Math::Vector3 GetRight() const;
		Math::Vector3 GetUp() const;
		Math::Vector3 GetBackward() const;
		Math::Vector3 GetLeft() const;
		Math::Vector3 GetDown() const;

		Math::Vector3 position;
		Math::Quaternion rotation;
		Math::Vector3 scale;
	};
}
