#pragma once

namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C class PHYSICS_API IGeometry
		: public IBase
	{
	public:
		virtual ~IGeometry() = default;

 		virtual void	SetScale(const Utils::Math::Vector3& position) = 0;
		virtual const	Utils::Math::Vector3 GetScale() const = 0;


		//TODO: Type & Scale
		virtual void SetType(Utils::DataStructure::GeometryShape type);
		virtual Utils::DataStructure::GeometryShape GetType(Utils::DataStructure::GeometryShape type);

	protected:
		Utils::DataStructure::GeometryShape type = Utils::DataStructure::GeometryShape::End;
	};
}
