#pragma once

namespace Engine::Input::Component
{
	struct IButtonComponent : Component
	{
	};

	struct ButtonComponent : IButtonComponent
	{
		virtual void Finalize() = 0;
	};
}
