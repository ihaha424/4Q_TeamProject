#pragma once

class EmptyWorld final : public Engine::World
{
public:
	EmptyWorld() = default;

	void Prepare(Engine::Content::Factory::Object* objectFactory) override;
};