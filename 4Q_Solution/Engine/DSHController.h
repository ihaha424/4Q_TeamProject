#pragma once
#include "Controller.h"

namespace Engine::DSHInput::Device
{
	class Controller final : public Input::Device::Controller
	{
	public:
		Controller();

		void Setup(DSH::Input::Device::IController* controller);

		void Update() override;
		void Reset() override;
		void Finalize() override;

		[[nodiscard]] bool IsButtonDown(Button button) const override;
		[[nodiscard]] bool IsButtonUp(Button button) const override;
		[[nodiscard]] bool IsButtonPressed(Button button) const override;
		[[nodiscard]] bool IsButtonReleased(Button button) const override;

		void GetComponent(Button button, Input::Component::IButtonComponent** component) override;
		void GetComponent(Trigger trigger, Input::Component::IAxisComponent** component) override;
		void GetComponent(Thumb thumb, Input::Component::IAxisComponent** component) override;

		void SetThumbStickSensitive(long sensitive) override;
		void SetTriggerSensitive(long sensitive) override;

	private:
		bool IsButtonState(Button button, std::function<bool(DSH::Input::Component::IButtonComponent*)> state) const;


		DSH::Input::Device::IController* _controller;

		std::unordered_map<Button, Input::Component::IButtonComponent*> _buttons;
		std::unordered_map<Trigger, Input::Component::IAxisComponent*> _triggers;
		std::unordered_map<Thumb, Input::Component::IAxisComponent*> _thumbs;

		std::unordered_map<Button, DSH::Input::Device::IController::Button> _buttonMap;
		std::unordered_map<Trigger, DSH::Input::Device::IController::Trigger> _triggerMap;
		std::unordered_map<Thumb, DSH::Input::Device::IController::Thumb> _thumbMap;
	};
}
