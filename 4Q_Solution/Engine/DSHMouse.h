#pragma once
#include "Mouse.h"

namespace Engine::DSHInput::Device
{
	class Mouse final : public Input::Device::Mouse
	{
	public:
		Mouse();

		void Setup(DSH::Input::Device::IMouse* mouse);

		void Update() override;
		void Reset() override;
		void Finalize() override;

		[[nodiscard]] Math::Point GetPosition() const override;

		[[nodiscard]] bool IsButtonDown(Button button) const override;
		[[nodiscard]] bool IsButtonUp(Button button) const override;
		[[nodiscard]] bool IsButtonPressed(Button button) const override;
		[[nodiscard]] bool IsButtonReleased(Button button) const override;

		void GetComponent(Button button, Input::Component::IButtonComponent** buttonComponent) override;
		void GetComponent(Axis axis, Input::Component::IAxisComponent** axisComponent) override;

		void ShowCursor() override;
		void HideCursor() override;

		void LockCursor() override;
		void UnlockCursor() override;

	private:
		bool IsButtonState(Button button, std::function<bool(DSH::Input::Component::IButtonComponent*)> state) const;

		DSH::Input::Device::IMouse* _mouse;

		std::unordered_map<Button, Input::Component::IButtonComponent*> _buttons;
		std::unordered_map<Axis, Input::Component::IAxisComponent*> _axes;

		std::unordered_map<Button, DSH::Input::Device::IMouse::Button> _buttonMap;
		std::unordered_map<Axis, DSH::Input::Device::IMouse::Axis> _axisMap;
	};
}
