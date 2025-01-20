#pragma once

namespace Engine::Input::Modifier
{
	struct ISwizzleAxis : Modifier
	{
		enum class Type : unsigned char
		{
			XYZ,
			XZY,
			YXZ,
			YZX,
			ZXY,
			ZYX,
			MAX
		};
	};

	struct SwizzleAxis : ISwizzleAxis
	{
		virtual void Finalize() = 0;

		virtual void SetType(Type type) = 0;
	};
}
