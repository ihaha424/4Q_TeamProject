#pragma once

namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C class PHYSICS_API IGeometry
		: virtual public IBase
	{
	public:
 		virtual void	SetScale(const Utils::Math::Vector3& position) = 0;
		virtual const	Utils::Math::Vector3 GetScale() const = 0;


		//TODO: Type & Scale
		virtual Utils::DataStructure::GeometryShape SetType(Utils::DataStructure::GeometryShape type);
		virtual void GetType(Utils::DataStructure::GeometryShape type);

	protected:
		Utils::DataStructure::GeometryShape type = Utils::DataStructure::GeometryShape::End;
	};
}
