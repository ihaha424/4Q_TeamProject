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

	private:
		Transform* _target;
		Camera* _camera;

		float _distance;

		Math::Matrix _matrix;
	};
}
