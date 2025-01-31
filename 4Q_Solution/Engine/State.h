#pragma once

namespace Engine::Component
{
	class State abstract
	{
	public:
		virtual unsigned int Update(float deltaTime) = 0;
		virtual void OnStart() = 0;
		virtual void OnExit() = 0;
		virtual void Reset() {}
	};
}
