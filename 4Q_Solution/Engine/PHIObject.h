#pragma once

#include "PhysicsObject.h"


namespace Engine::PHI
{
	class Object final
		: public Physics::Object
	{
	public:
		void Initialize() override;
		void Update(float deltaTime) const override;
		void Finalize() override;

	private:
		PhysicsEngineAPI::IObject* object;
	};
}