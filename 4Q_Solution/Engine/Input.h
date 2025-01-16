#pragma once

namespace Engine::Manager
{
	struct IInput
	{
		IInput() = default;
		IInput(const IInput& other) = default;
		IInput(IInput&& other) noexcept = default;
		IInput& operator=(const IInput& other) = default;
		IInput& operator=(IInput&& other) noexcept = default;
		virtual ~IInput() = default;
	};

	class Input final : public IInput
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