#pragma once

namespace GameClient
{
	class Application final : public Engine::Application
	{
	public:
		explicit Application(HINSTANCE instanceHandle);

	protected:
		void DeclareInputActions(Engine::Input::IManager* inputManager) override;
		void PrepareInitialWorld(Engine::Content::Factory::World* worldFactory) override;
	};
}
