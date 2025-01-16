#pragma once

class GameApplication : public Engine::Application
{
public:
	explicit GameApplication(HINSTANCE instanceHandle);

private:
	std::vector<Engine::World*> _worlds;
};

