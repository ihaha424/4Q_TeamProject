#pragma once

class Player : public Engine::Object
{
protected:
	void PreInitialize() override;


private:
	Engine::Component::MovementComponent* _movement;
};

