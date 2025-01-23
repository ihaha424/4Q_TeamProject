#pragma once

namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C class PHYSICS_API IMaterial
		: public IBase
	{
	public:
		virtual void setRestitutionCombineMode() = 0;
	};
}

