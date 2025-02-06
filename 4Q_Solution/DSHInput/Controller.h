#pragma once

namespace DSH::Input
{
	namespace Component
	{
		class ButtonComponent;
		class AxisComponent;
	}

	namespace Device
	{
		class Controller final : public IController
		{
			static constexpr DWORD CONTROLLER_UNKNOWN_INDEX = -1;
			static constexpr LONG THUMB_STICK_SENSITIVE = (std::numeric_limits<decltype(XINPUT_GAMEPAD::sThumbLX)>::max)();
			static constexpr LONG TRIGGER_SENSITIVE = (std::numeric_limits<decltype(XINPUT_GAMEPAD::bLeftTrigger)>::max)();

			enum ConnectionState : unsigned char
			{
				Connected,
				Disconnected,
			};

		public:
			Controller();
			~Controller() override;

			HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
			ULONG AddRef() override;
			ULONG Release() override;

			void Update() override;
			void Reset() override;

			void SetControllerIndex(DWORD index) override;

			HRESULT GetComponent(Button button, Component::IButtonComponent** ppComponent) override;
			HRESULT GetComponent(Trigger trigger, Component::IAxisComponent** ppComponent) override;
			HRESULT GetComponent(Thumb thumb, Component::IAxisComponent** ppComponent) override;

			void SetThumbStickSensitive(LONG sensitive) override;
			void SetTriggerSensitive(LONG sensitive) override;

		private:
			static WORD GetFlag(Button button);
			BYTE* GetTriggerValuePointer(Trigger trigger);
			SHORT* GetThumbValuePointer(Thumb thumb);
			[[nodiscard]] bool CheckConnection();

			ULONG _referenceCount;

			LONG _thumbStickSensitive;
			LONG _triggerSensitive;

			ConnectionState _connectionState;
			BYTE _connectPendingCount;

			DWORD _controllerIndex;
			XINPUT_STATE _state;

			std::unordered_map<Button, WORD> _buttonFlags;
			std::unordered_map<Button, Component::ButtonComponent*> _buttons;

			std::unordered_map<Trigger, BYTE*> _triggerValues;
			std::unordered_map<Trigger, Component::AxisComponent*> _triggers;

			std::unordered_map<Thumb, SHORT*> _thumbValues;
			std::unordered_map<Thumb, Component::AxisComponent*> _thumbs;
		};

	}
}
