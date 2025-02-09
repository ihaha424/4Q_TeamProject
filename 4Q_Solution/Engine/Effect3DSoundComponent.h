#pragma once

namespace Engine::Component
{
	class Effect3DSound final : public Sound
	{
	public:
		Effect3DSound() = default;

		void Initialize(const Modules& modules) override;

		void SetPosition(const Math::Vector3& position) const;
		void SetVelocity(const Math::Vector3& velocity) const;

		void SetMaxDistance(float maxDistance) const;
		void SetMinDistance(float minDistance) const;

	private:
		DSH::Audio::ISound3D* _sound3D;
	};
}