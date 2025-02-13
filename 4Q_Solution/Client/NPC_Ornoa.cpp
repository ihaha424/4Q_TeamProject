#include "pch.h"
#include "NPC_Ornoa.h"

NPC_Ornoa::NPC_Ornoa():
	NPC(L"Assets/Models/NPC_Ornoa.fbx",
		Engine::Math::Matrix::CreateScale(0.1f, 0.1f, 0.1f)*
		Engine::Math::Matrix::CreateRotationY(60.0f / 180.0f * std::numbers::pi_v<float>)*
		Engine::Math::Matrix::CreateTranslation(-924.8f, 0.0f, -820.5f))
{
}
