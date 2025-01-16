#pragma once

namespace Engine::Component
{
	class MovementComponent :
		public Component
	{
	public:
		MovementComponent();

		void SetSpeed(float speed);
		[[nodiscard]] float GetSpeed() const;

		void SetDirection(Math::Vector3 direction);

	private:
		float _speed;
		Math::Vector3 _direction;
	};
}

