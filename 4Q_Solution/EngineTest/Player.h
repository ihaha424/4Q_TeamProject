#pragma once

namespace Engine::Component
{
	class Movement;
}

class Player : public Engine::Object
{
protected:
	void PreInitialize() override;
private:
	Engine::Component::Movement* _movement;
};

