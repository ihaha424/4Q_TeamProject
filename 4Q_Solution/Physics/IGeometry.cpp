#include "pch.h"
#include "IGeometry.h"


namespace PhysicsEngineAPI
{
	void IGeometry::SetType(Utils::DataStructure::GeometryShape _type)
	{
		_type = type;
	}
	Utils::DataStructure::GeometryShape IGeometry::GetType(Utils::DataStructure::GeometryShape type)
	{
		return type;
	}
}

