#pragma once

namespace Physics
{
	namespace Utils
	{
		namespace Math
		{
			EXTERN_C union PHYSICS_API Vector3
			{
				float value[3];
				struct
				{
					float x, y, z;
				};
			};
			EXTERN_C union PHYSICS_API Vector4
			{
				float value[4];
				struct
				{
					float x, y, z, w;
				};
			};
			EXTERN_C struct PHYSICS_API Transform
			{
				Transform(Vector3 _position) { position = _position; rotation = { 0,0,0,1 }; };
				Transform(Vector4 _rotation) { position = { 0,0,0 }; rotation = _rotation; };
				Transform(Vector3 pos = { 0,0,0 }, Vector4 rot = { 0,0,0,1 }) { position = pos; rotation = rot; }
				~Transform() = default;
				Vector3 position;
				Vector4 rotation;
			};
		}
	}
}
