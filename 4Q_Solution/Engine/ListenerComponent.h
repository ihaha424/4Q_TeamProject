#pragma once

namespace Engine::Component
{
	class Listener final : public Component
	{
	public:
		Listener();

		void Initialize(const Modules& modules) override;
		void Finalize() override;

		void Setup(const Math::Vector3& forward, const Math::Vector3& up);

		void SetPosition(const Math::Vector3& position) const;
		void SetVelocity(const Math::Vector3& velocity) const;
		void SetForward(const Math::Vector3& forward);
		void SetUpward(const Math::Vector3& up);

	private:
		DSH::Audio::IListener* _listener;

		Math::Vector3 _up;
		Math::Vector3 _forward;
	};
}
