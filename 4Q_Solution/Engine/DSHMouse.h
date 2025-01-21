#pragma once
#include "Mouse.h"

namespace Engine::DSHInput::Device
{
	class Mouse final : public Input::Device::Mouse
	{
	public:
		Mouse();

		void Setup(DSH::Input::Device::IMouse* mouse);

		void Initialize() override;
		void Update() override;
		void Reset() override;
		void Finalize() override;

		[[nodiscard]] Math::Point GetPosition() const override;

		[[nodiscard]] bool IsButtonDown(Button button) const override;
		[[nodiscard]] bool IsButtonUp(Button button) const override;
		[[nodiscard]] bool IsButtonPressed(Button button) const override;
		[[nodiscard]] bool IsButtonReleased(Button button) const override;

	private:
		DSH::Input::Device::IMouse* _mouse;

		std::unordered_map<Button, DSH::Input::Device::IMouse::Button> _buttonMap;
	};
}
