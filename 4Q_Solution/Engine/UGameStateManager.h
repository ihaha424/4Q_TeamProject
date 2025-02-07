#pragma once

namespace Engine::UGameState
{
	class Manager final : public Engine::GameState::Manager
	{
	public:
		Manager();

		void RegisterSubManager(IManager* _subManager) override;
		void AttachEvent(std::wstring _event) override;


		void Initialize() override;
		void Update(float deltaTime) override;
		void Finalize() override;

	};
}

