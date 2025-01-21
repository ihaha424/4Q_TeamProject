#pragma once

namespace Engine::Input::Trigger
{
	struct IDown : Trigger
	{
		
	};

	struct Down : IDown
	{
		virtual void Finalize() = 0;
	};
}
