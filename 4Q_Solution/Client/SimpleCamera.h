#pragma once

class SimpleCamera final : public Engine::Object
{
public:
	SimpleCamera();

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void PreInitialize(const Engine::Modules& modules) override;
	void PostAttach() override;
protected:
	void DisposeComponents() override;

private:
	Engine::Component::Camera* _camera;
};