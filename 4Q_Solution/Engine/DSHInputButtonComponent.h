#pragma once

namespace Engine::DSHInput::Component
{
	class ButtonComponent final : public Input::Component::ButtonComponent
	{
	public:
		ButtonComponent();

		void Setup(DSH::Input::Component::IButtonComponent* button);

		void Finalize() override;

		DSH::Input::Component::IButtonComponent* Get() const;

	private:
		DSH::Input::Component::IButtonComponent* _button;
	};
}