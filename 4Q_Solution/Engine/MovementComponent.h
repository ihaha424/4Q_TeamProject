#pragma once

namespace Engine::Component
{
	class MovementComponent :
		public Component
	{
	public:
		void Initialize() override;

		void SetSpeed(float speed);
		[[nodiscard]] float GetSpeed() const;

	private:
		float _speed;
	};
}

