#pragma once
#include "Controller.h"

namespace Engine::DSHInput::Device
{
	class Controller final : public Input::Device::Controller
	{
	public:
		Controller();

		void Setup(DSH::Input::Device::IController* controller);

		void Initialize() override;
		void Update() override;
		void Reset() override;
		void Finalize() override;

		[[nodiscard]] bool IsButtonDown(Button button) const override;
		[[nodiscard]] bool IsButtonUp(Button button) const override;
		[[nodiscard]] bool IsButtonPressed(Button button) const override;
		[[nodiscard]] bool IsButtonReleased(Button button) const override;

	private:
		DSH::Input::Device::IController* _controller;

		std::unordered_map<Button, DSH::Input::Device::IController::Button> _buttonMap;
	};
}
