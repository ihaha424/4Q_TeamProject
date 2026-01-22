#pragma once

namespace Engine::Input::Component
{
	struct IAxisComponent : Component
	{
	};

	struct AxisComponent : IAxisComponent
	{
		virtual void Finalize() = 0;
	};
}