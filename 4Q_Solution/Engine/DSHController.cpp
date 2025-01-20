#include "pch.h"
#include "DSHController.h"

Engine::DSHInput::Device::Controller::Controller():
	_controller(nullptr)
{
	for (unsigned char button = 0; button < static_cast<unsigned char>(Button::Max); ++button)
	{
		_buttonMap[static_cast<Button>(button)] = static_cast<DSH::Input::Device::IController::Button>(button);
	}
}

void Engine::DSHInput::Device::Controller::Setup(DSH::Input::Device::IController* controller)
{
	controller->AddRef();
	_controller = controller;
}

void Engine::DSHInput::Device::Controller::Initialize()
{
}

void Engine::DSHInput::Device::Controller::Update()
{
	_controller->Update();
}

void Engine::DSHInput::Device::Controller::Reset()
{
	_controller->Reset();
}

void Engine::DSHInput::Device::Controller::Finalize()
{
	Utility::SafeRelease()(&_controller, "Controller is still being referenced.");
}

bool Engine::DSHInput::Device::Controller::IsButtonDown(Button button) const
{
	// TODO: Implement this function.
}

bool Engine::DSHInput::Device::Controller::IsButtonUp(Button button) const
{
	// TODO: Implement this function.
}

bool Engine::DSHInput::Device::Controller::IsButtonPressed(Button button) const
{
	// TODO: Implement this function.
}

bool Engine::DSHInput::Device::Controller::IsButtonReleased(Button button) const
{
	// TODO: Implement this function.
}
