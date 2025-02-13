#pragma once
#include "NPC.h"

class NPC_Ornoa_Elder : public NPC
{
public:
	NPC_Ornoa_Elder();

	void PostInitialize(const Engine::Modules& modules) override;
};

