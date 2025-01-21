#pragma once

namespace Engine::Input::Device
{
	struct IController
	{
		enum class Button : unsigned char
		{
			DpadUp,
			DpadDown,
			DpadLeft,
			DpadRight,
			Start,
			Back,
			LeftThumb,
			RightThumb,
			LeftShoulder,
			RightShoulder,
			Padding1,
			Padding2,
			A,
			B,
			X,
			Y,
			Max
		};

		enum class Trigger : unsigned char
		{
			Left,
			Right,
			Max
		};

		enum class Thumb : unsigned char
		{
			LeftX,
			LeftY,
			RightX,
			RightY,
			Max
		};

		IController() = default;
		IController(const IController& other) = default;
		IController(IController&& other) noexcept = default;
		IController& operator=(const IController& other) = default;
		IController& operator=(IController&& other) noexcept = default;
		virtual ~IController() = default;

		[[nodiscard]] virtual bool IsButtonDown(Button button) const = 0;
		[[nodiscard]] virtual bool IsButtonUp(Button button) const = 0;
		[[nodiscard]] virtual bool IsButtonPressed(Button button) const = 0;
		[[nodiscard]] virtual bool IsButtonReleased(Button button) const = 0;
	};

	struct Controller : IController
	{
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Reset() = 0;
		virtual void Finalize() = 0;
	};
}