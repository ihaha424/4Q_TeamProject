#pragma once

namespace Engine::Input::Modifier
{
	struct INegative : Modifier
	{
	};

	struct Negative : INegative
	{
		virtual void Finalize() = 0;
	};
}