#pragma once

class TestSprite : public Engine::Object
{
public:
	TestSprite();

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

private:
	Engine::Math::Matrix _worldMatrix;
	Engine::Component::Sprite* _sprite;
};