#pragma once

namespace Engine::Component
{
	class RigidComponent : public Component
	{
	public:
		Engine::Physics::IRigidComponent* rigidComponent;

	};
}
