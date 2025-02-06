#pragma once

namespace Engine::Component
{
	class Camera;
	class FixedArm : public Component
	{
	public:
		FixedArm();

		void SetDistance(float distance);
		void SetTarget(Transform* target);
		void SetCameraComponent(Camera* camera);

		void Initialize(const Modules& modules) override;

		void Update(float deltaTime) override;

		void Rotate(const Math::Vector3& value);

		void SetCameraPosition(const Math::Vector2& value);

		void SetRotationSpeed(const Math::Vector2& speed);

		[[nodiscard]] Math::Vector3 GetForward() const;
		[[nodiscard]] Math::Vector3 GetTransformDirection(const Math::Vector3& direction) const;
		[[nodiscard]] Math::Quaternion GetForwardRotation() const;
		[[nodiscard]] Math::Quaternion GetRotation(const Math::Vector3& direction) const;
		void FollowDirection(const Math::Vector3& direction);

		void SetFollowSpeed(float speed);

	private:
		Transform* _target;
		Camera* _camera;

		float _distance;

		Math::Vector2 _rotationSpeed;

		Math::Vector3 _rotation;
		Math::Vector2 _cameraPosition;
		Math::Matrix _matrix;

		float _followSpeed;
	};
}
