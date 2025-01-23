#pragma once

#include "PhysicsStaticObject.h"

namespace Engine::PHI
{
	class StaticObject final
		: public Physics::StaticObject
	{
	public:
		void Initialize() override;
		void Update(float deltaTime) const override;
		void Finalize() override;

	private:
		PhysicsEngineAPI::IStaticObject* object;
	};
}