#pragma once

class RemoteLive : public Remote
{
public:
	RemoteLive(std::filesystem::path&& meshPath);

public:
	void PostInitialize(const Engine::Modules& modules) override;
};

