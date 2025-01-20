#pragma once

namespace Engine::Input
{
	union Value
	{
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


		// Constants
		static const Value Zero;
	};
}
