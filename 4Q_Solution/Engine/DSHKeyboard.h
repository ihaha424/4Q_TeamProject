#pragma once
#include "Keyboard.h"

namespace Engine::DSHInput::Device
{
	class Keyboard final : public Input::Device::Keyboard
	{
	public:
		Keyboard();

		void Setup(DSH::Input::Device::IKeyboard* keyboard);

		void Update() override;
		void Reset() override;
		void Finalize() override;

		[[nodiscard]] bool IsKeyDown(Key key) const override;
		[[nodiscard]] bool IsKeyUp(Key key) const override;
		[[nodiscard]] bool IsKeyPressed(Key key) const override;
		[[nodiscard]] bool IsKeyReleased(Key key) const override;

		void GetComponent(Key key, Input::Component::IButtonComponent** buttonComponent) override;

	private:
		bool IsButtonState(Key key, std::function<bool(DSH::Input::Component::IButtonComponent*)> state) const;

		DSH::Input::Device::IKeyboard* _keyboard;

		std::unordered_map<Key, Input::Component::IButtonComponent*> _buttons;

		std::unordered_map<Key, DSH::Input::Device::IKeyboard::Key> _keyMap;
	};
}
