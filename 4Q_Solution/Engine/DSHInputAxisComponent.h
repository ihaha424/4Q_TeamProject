#pragma once

namespace Engine::DSHInput::Component
{
	class AxisComponent final : public Input::Component::AxisComponent
	{
	public:
		AxisComponent();
		void Setup(DSH::Input::Component::IAxisComponent* axis);
		void Finalize() override;
		DSH::Input::Component::IAxisComponent* Get() const;

	private:
		DSH::Input::Component::IAxisComponent* _axis;
	};
}
