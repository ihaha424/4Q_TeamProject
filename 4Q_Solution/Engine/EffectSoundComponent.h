#pragma once

namespace Engine::Component
{
	class EffectSound : public Sound
	{
	public:
		EffectSound() = default;

		void Initialize(const Modules& modules) override;
	};
}
