#include "pch.h"
#include "Controller.h"

#include "ButtonComponent.h"
#include "AxisComponent.h"

DSH::Input::Device::Controller::Controller() :
	_referenceCount(1), _connectionState(Disconnected), _connectPendingCount(0),
	_controllerIndex(CONTROLLER_UNKNOWN_INDEX), _state{}
{
}

DSH::Input::Device::Controller::~Controller()
{
	std::ranges::for_each(_buttons | std::views::values, [](Component::ButtonComponent* button) { button->Release(); });
	_buttons.clear();
	std::ranges::for_each(_triggers | std::views::values, [](Component::AxisComponent* axis) { axis->Release(); });
	_triggers.clear();
	std::ranges::for_each(_thumbs | std::views::values, [](Component::AxisComponent* thumb) { thumb->Release(); });
	_thumbs.clear();
}

HRESULT DSH::Input::Device::Controller::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IController &&
		riid != IID_IDevice &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Device::Controller::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Device::Controller::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

void DSH::Input::Device::Controller::Update()
{
	if (_connectionState == Disconnected && !CheckConnection()) return;


	if (XInputGetState(_controllerIndex, &_state) != ERROR_SUCCESS)
	{
		_connectionState = Disconnected;
		_state = {};
		return;
	}

	std::ranges::for_each(_buttons, [this](const std::pair<const Button, Component::ButtonComponent*>& buttonPair) { buttonPair.second->SetValue(_buttonFlags[buttonPair.first] & _state.Gamepad.wButtons); });
	std::ranges::for_each(_triggers, [this](const std::pair<const Trigger, Component::AxisComponent*>& axisPair) { axisPair.second->SetAbsoluteValue(*_triggerValues[axisPair.first]); });
	std::ranges::for_each(_thumbs, [this](const std::pair<const Thumb, Component::AxisComponent*>& axisPair) { axisPair.second->SetAbsoluteValue(*_thumbValues[axisPair.first]); });
}

void DSH::Input::Device::Controller::Reset()
{
	std::ranges::for_each(_buttons | std::views::values, [](Component::ButtonComponent* button) { button->Reset(); });
	std::ranges::for_each(_triggers | std::views::values, [](Component::AxisComponent* axis) { axis->Reset(); });
	std::ranges::for_each(_thumbs | std::views::values, [](Component::AxisComponent* thumb) { thumb->Reset(); });
}

void DSH::Input::Device::Controller::SetControllerIndex(const DWORD index)
{
	_controllerIndex = index;
}

HRESULT DSH::Input::Device::Controller::GetComponent(const Button button, Component::IButtonComponent** ppComponent)
{
	if (button == Button::Max) return E_INVALIDARG;
	if (ppComponent == nullptr) return E_INVALIDARG;
	Component::ButtonComponent* pButtonComponent = nullptr;
	if (_buttons.contains(button) == false)
	{
		pButtonComponent = new Component::ButtonComponent();
		if (pButtonComponent == nullptr) return E_OUTOFMEMORY;
		_buttons[button] = pButtonComponent;
		_buttonFlags[button] = GetFlag(button);
	}
	else pButtonComponent = _buttons[button];
	pButtonComponent->AddRef();
	*ppComponent = pButtonComponent;
	return S_OK;
}

HRESULT DSH::Input::Device::Controller::GetComponent(const Trigger trigger, Component::IAxisComponent** ppComponent)
{
	if (trigger == Trigger::Max) return E_INVALIDARG;
	if (ppComponent == nullptr) return E_INVALIDARG;
	Component::AxisComponent* pAxisComponent = nullptr;
	if (_triggers.contains(trigger) == false)
	{
		pAxisComponent = new Component::AxisComponent();
		if (pAxisComponent == nullptr) return E_OUTOFMEMORY;
		pAxisComponent->SetSensitivity(TRIGGER_SENSITIVE);
		pAxisComponent->SetDeadZone(XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		_triggers[trigger] = pAxisComponent;
		_triggerValues[trigger] = GetTriggerValuePointer(trigger);
	}
	else pAxisComponent = _triggers[trigger];
	pAxisComponent->AddRef();
	*ppComponent = pAxisComponent;
	return S_OK;
}

HRESULT DSH::Input::Device::Controller::GetComponent(const Thumb thumb, Component::IAxisComponent** ppComponent)
{
	if (thumb == Thumb::Max) return E_INVALIDARG;
	if (ppComponent == nullptr) return E_INVALIDARG;
	Component::AxisComponent* pAxisComponent = nullptr;
	if (_thumbs.contains(thumb) == false)
	{
		pAxisComponent = new Component::AxisComponent();
		if (pAxisComponent == nullptr) return E_OUTOFMEMORY;
		if (thumb == Thumb::LeftX || thumb == Thumb::LeftY) pAxisComponent->SetDeadZone(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		if (thumb == Thumb::RightX || thumb == Thumb::RightY) pAxisComponent->SetDeadZone(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		pAxisComponent->SetSensitivity(THUMB_STICK_SENSITIVE);
		_thumbs[thumb] = pAxisComponent;
		_thumbValues[thumb] = GetThumbValuePointer(thumb);
	}
	else pAxisComponent = _thumbs[thumb];
	pAxisComponent->AddRef();
	*ppComponent = pAxisComponent;
	return S_OK;
}

WORD DSH::Input::Device::Controller::GetFlag(Button button)
{
	WORD flag = 1;
	for (unsigned char i = 0; i < static_cast<unsigned char>(button); ++i) flag = flag << 1;
	return flag;
}

BYTE* DSH::Input::Device::Controller::GetTriggerValuePointer(const Trigger trigger)
{
	switch (trigger)
	{
	case Trigger::Left:
		return &_state.Gamepad.bLeftTrigger;
	case Trigger::Right:
		return &_state.Gamepad.bRightTrigger;
	case Trigger::Max:
		break;
	}
	return nullptr;
}

SHORT* DSH::Input::Device::Controller::GetThumbValuePointer(const Thumb thumb)
{
	switch (thumb) {
	case Thumb::LeftX:
		return &_state.Gamepad.sThumbLX;
	case Thumb::LeftY:
		return &_state.Gamepad.sThumbLY;
	case Thumb::RightX:
		return &_state.Gamepad.sThumbRX;
	case Thumb::RightY:
		return &_state.Gamepad.sThumbRY;
	case Thumb::Max:
		break;
	}
	return nullptr;
}

bool DSH::Input::Device::Controller::CheckConnection()
{
	if (++_connectPendingCount < 0xFF) return false;
	_connectPendingCount = 0;
	if (_controllerIndex == CONTROLLER_UNKNOWN_INDEX)
	{
		for (int i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			if (XInputGetState(i, &_state) == ERROR_SUCCESS)
			{
				_controllerIndex = i;
				break;
			}
		}
	}
	else if (XInputGetState(_controllerIndex, &_state) != ERROR_SUCCESS) return false;
	_connectionState = Connected;
	return true;
}
