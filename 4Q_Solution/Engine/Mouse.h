#pragma once

namespace Engine::Input::Device
{
	struct IMouse
	{
		enum class Button : unsigned char
		{
			Left = VK_LBUTTON,
			Right = VK_RBUTTON,
			Middle = VK_MBUTTON,
			X1 = VK_XBUTTON1,
			X2 = VK_XBUTTON2,
			Max = 0x07
		};

		enum class Axis : unsigned char
		{
			X,
			Y,
			Wheel,
			Max
		};

		IMouse() = default;
		IMouse(const IMouse& other) = default;
		IMouse(IMouse&& other) noexcept = default;
		IMouse& operator=(const IMouse& other) = default;
		IMouse& operator=(IMouse&& other) noexcept = default;
		virtual ~IMouse() = default;

		[[nodiscard]] virtual Math::Point GetPosition() const = 0;
		[[nodiscard]] virtual bool IsButtonDown(Button button) const = 0;
		[[nodiscard]] virtual bool IsButtonUp(Button button) const = 0;
		[[nodiscard]] virtual bool IsButtonPressed(Button button) const = 0;
		[[nodiscard]] virtual bool IsButtonReleased(Button button) const = 0;

		virtual void GetComponent(Button button, Component::IButtonComponent** buttonComponent) = 0;
		virtual void GetComponent(Axis axis, Component::IAxisComponent** axisComponent) = 0;
	};

	struct Mouse : IMouse
	{
		virtual void Update() = 0;
		virtual void Reset() = 0;
		virtual void Finalize() = 0;
	};
}
