#pragma once


namespace DSH::Input::Component
{
	class ButtonComponent;
}

namespace DSH::Input
{
	namespace Component
	{
		class AxisComponent;
	}
	namespace Device
	{
		class Mouse final : public IMouse
		{
			static constexpr LONG MOUSE_SENSITIVE = 100;
		public:
			Mouse();
			~Mouse() override;

			HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
			ULONG AddRef() override;
			ULONG Release() override;

			void Update() override;
			void Reset() override;

			void SetHandle(HWND handle) override;

			HRESULT GetComponent(Button button, Component::IButtonComponent** ppComponent) override;
			HRESULT GetComponent(Axis axis, Component::IAxisComponent** ppComponent) override;

			[[nodiscard]] Value GetPosition() const override;

			void ShowCursor() override;
			void HideCursor() override;

			void LockCursor() override;
			void UnlockCursor() override;

		private:
			void UpdateAxes();
			void UpdateButtons();
			void SetCursorToCenter() const;

			void ResetAxes();
			void ResetButtons();

			ULONG _referenceCount;

			HWND _handle;

			std::unordered_map<Axis, Component::AxisComponent*> _axes;
			std::unordered_map<Button, Component::ButtonComponent*> _buttons;

			bool _isCursorLock;

			POINT _screenCenter;
		};
	}
}
