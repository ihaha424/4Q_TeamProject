#pragma once

namespace Engine::Input::Modifier
{
	struct ISwizzleAxis
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

		ISwizzleAxis() = default;
		ISwizzleAxis(const ISwizzleAxis& other) = default;
		ISwizzleAxis(ISwizzleAxis&& other) noexcept = default;
		ISwizzleAxis& operator=(const ISwizzleAxis& other) = default;
		ISwizzleAxis& operator=(ISwizzleAxis&& other) noexcept = default;
		virtual ~ISwizzleAxis() = default;
	};

	struct SwizzleAxis : ISwizzleAxis
	{
		virtual void Finalize() = 0;

		virtual void SetType(Type type) = 0;
	};
}
