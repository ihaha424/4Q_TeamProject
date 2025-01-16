#pragma once

namespace Engine::Component
{
	class Movement;
}

class Player : public Engine::Object
{
public:
	void Initialize() override;
	
private:
	Engine::Component::Movement* _movement;
};

