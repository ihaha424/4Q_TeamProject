#include "pch.h"
#include "IGeometry.h"


namespace Physics
{
	Utils::DataStructure::GeometryShape IGeometry::SetType(Utils::DataStructure::GeometryShape type)
	{
		return Utils::DataStructure::GeometryShape::End;
	}
	void IGeometry::GetType(Utils::DataStructure::GeometryShape _type)
	{
		_type = type;
	}
}

