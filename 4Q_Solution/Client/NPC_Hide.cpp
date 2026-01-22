#include "pch.h"
#include "NPC_Hide.h"

NPC_Hide::NPC_Hide():
	NPC(L"Assets/Models/NPC_Hide_Leader.fbx",
		Engine::Math::Matrix::CreateScale(0.1f, 0.1f, 0.1f) *
		Engine::Math::Matrix::CreateRotationY(234.6f / 180.0f * std::numbers::pi_v<float>)*
		Engine::Math::Matrix::CreateTranslation(649.8f, 0.0f, 153.6f))
{
}
