#pragma once

class BermioreFabricLight : public Engine::Object
{
public:
	BermioreFabricLight();

public:
	// Object을(를) 통해 상속됨
	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	void PostUpdate(float deltaTime) override;

private:
	Engine::Component::Light* _light[6];
	Engine::Math::Vector3 _position;
};