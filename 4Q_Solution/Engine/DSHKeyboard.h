#pragma once
#include "Keyboard.h"

namespace Engine::DSHInput::Device
{
	class Keyboard final : public Input::Device::Keyboard
	{
	public:
		Keyboard();

		void Setup(DSH::Input::Device::IKeyboard* keyboard);

		void Initialize() override;
		void Update() override;
		void Reset() override;
		void Finalize() override;

		[[nodiscard]] bool IsKeyDown(Key key) const override;
		[[nodiscard]] bool IsKeyUp(Key key) const override;
		[[nodiscard]] bool IsKeyPressed(Key key) const override;
		[[nodiscard]] bool IsKeyReleased(Key key) const override;

		void GetComponent(Key key, Input::Component::IButtonComponent** button) override;

	private:
		DSH::Input::Device::IKeyboard* _keyboard;

		std::unordered_map<Key, DSH::Input::Device::IKeyboard::Key> _keyMap;
		std::unordered_map<Key, Input::Component::IButtonComponent*> _buttons;
	};
}
