#pragma once

namespace DSH::Input
{
	EXTERN_C union DSH_INPUT_LIBRARY_API Value
	{
		Value();
		Value(float x, float y, float z);

		static Value Zero();

		Value& operator+=(const Value& rhs);

		bool operator==(const Value& rhs) const;

		operator bool() const;

		struct
		{
			short _;
			bool on;
		};
		struct
		{
			float scalar;
		};
		struct
		{
			float x;
			float y;
			float z;
		};
	};
}
