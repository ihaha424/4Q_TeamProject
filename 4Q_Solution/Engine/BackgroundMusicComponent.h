#pragma once

namespace Engine::Component
{
	class BackgroundMusic : public Sound
	{
	public:
		BackgroundMusic() = default;

		void Initialize(const Modules& modules) override;
	};
}
