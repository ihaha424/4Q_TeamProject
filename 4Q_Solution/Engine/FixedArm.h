#pragma once

namespace Engine::Component
{
	class Camera;
	class FixedArm : public Component
	{
	public:
		void SetDistance(float distance);
		void SetTarget
		void SetCameraComponent(Camera* camera);

	private:
		Transform* _target;
		Camera* _camera;

		float _distance;
	};
}
