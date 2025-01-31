#pragma once

class GlobalLight : public Engine::Object
{
public:
	GlobalLight() = default;
	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;
	
	void PostInitialize(const Engine::Modules& modules) override;

private:
	Engine::Component::Light* _globalLight;
	Engine::Component::Light* _pointLight;
};