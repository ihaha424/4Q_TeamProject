#pragma once

class GlobalLight : public Engine::Object
{
protected:
	void Addition() override;
	void PostInitialize() override;

private:
	Engine::Component::Light _globalLight;
	Engine::Component::Light _pointLight;
};