#pragma once

class GlobalLight : public Engine::Object
{
public:
	GlobalLight();
	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;
	
	void PostInitialize(const Engine::Modules& modules) override;

private:
	std::vector<Engine::Component::Light*> _pointLights;
	Engine::Component::Light* _globalLight;
};