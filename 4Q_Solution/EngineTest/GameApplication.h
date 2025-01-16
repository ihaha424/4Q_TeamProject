#pragma once

class GameApplication : public Engine::Application
{
public:
	explicit GameApplication(HINSTANCE instanceHandle);

protected:
	void DeclareInputActions(Engine::Manager::IInput* inputManager) override;

private:
	std::vector<Engine::World*> _worlds;
};

