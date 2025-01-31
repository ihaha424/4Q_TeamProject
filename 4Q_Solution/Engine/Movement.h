#pragma once

namespace Engine::Component
{
	class Movement : public Component
	{
	public:
		Movement();

		void SetTarget(Transform* target);

		void SetSpeed(float speed);
		[[nodiscard]] float GetSpeed() const;

		void SetDirection(Math::Vector3 direction);
		Engine::Math::Vector3 GetDirection() const;

		void Update(float deltaTime) override;

	private:
		float _speed;
		Math::Vector3 _direction;
		Transform* _target;
	};
}

