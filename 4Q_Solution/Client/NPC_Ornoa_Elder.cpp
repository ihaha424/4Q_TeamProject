#include "pch.h"
#include "NPC_Ornoa_Elder.h"

NPC_Ornoa_Elder::NPC_Ornoa_Elder():
	NPC(L"Assets/Models/NPC_Ornoa_Elder.fbx",
		Engine::Math::Matrix::CreateScale(0.1f, 0.1f, 0.1f)*
		Engine::Math::Matrix::CreateRotationY(60.0f / 180.0f * std::numbers::pi_v<float>)*
		Engine::Math::Matrix::CreateTranslation(-915.9f, 0.01f, -834.3f))
{
}

void NPC_Ornoa_Elder::PostInitialize(const Engine::Modules& modules)
{
	NPC::PostInitialize(modules);
	_animator->ChangeAnimation("Rig|Anim_Idle_NPC_Elder");
}
