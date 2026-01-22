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
		void FixedUpdate() override;

		void BindOnMove(std::function<void()> onMove);

		void BindOnStop(std::function<void()> onStop);

	protected:
		virtual void UpdateVelocity(float deltaTime);
		void SetIsMoving(bool isMoving);

		Transform* _target;

		Math::Vector3 _direction;
		float _speed;

		Math::Vector3 _velocity;

		bool _isMoving;
		bool _isMoved;

	private:

		std::function<void()> _onMove;
		std::function<void()> _onStop;
	};
}

