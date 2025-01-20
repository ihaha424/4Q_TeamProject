#pragma once

namespace DSH::Input::Modifier
{
	EXTERN_C const IID IID_ISwizzleAxis;

	EXTERN_C MIDL_INTERFACE("e1398a28-ac2f-4bbc-b3a3-d8a577e6c815")
		DSH_INPUT_LIBRARY_API ISwizzleAxis : IModifier
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

		virtual void SetType(
			/* [annotation][in] */
			_In_ Type type) = 0;
	};
}
