#pragma once

class Live : public Player
{
public:
	Live(std::filesystem::path&& meshPath);

public:
	void PostInitialize(const Engine::Modules& modules) override;
};