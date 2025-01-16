#pragma once

namespace Engine::Manager
{
	class Input
	{
	public:
		Input() = default;

		void Initialize(HWND windowHandle);
		void Update(float deltaTime) const;
		void Reset() const;
		void Finalize();

	private:
		DSH::Input::ISystem* _system;
		DSH::Input::Device::IKeyboard* _keyboard;
		DSH::Input::Device::IMouse* _mouse;
	};
}