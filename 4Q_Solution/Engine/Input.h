#pragma once

namespace Engine::Manager
{
	struct IInput
	{
		IInput() = default;
		IInput(const IInput& other) = default;
		IInput(IInput&& other) noexcept = default;
		IInput& operator=(const IInput& other) = default;
		IInput& operator=(IInput&& other) noexcept = default;
		virtual ~IInput() = default;

		virtual void AddActionListener(std::wstring_view actionName, DSH::Input::Trigger::Event event, const std::function<void(DSH::Input::Value value)>& listener) = 0;
		virtual DSH::Input::IMappingContext* GetMappingContext() = 0; // TODO: Remove this.
		virtual DSH::Input::Device::IKeyboard* GetKeyboard() = 0; // TODO: Remove this.
		virtual DSH::Input::ISystem* GetSystem() = 0; // TODO: Remove this.
	};

	class Input final : public IInput
	{
	public:
		Input() = default;

		void Initialize(HWND windowHandle);
		void Update(float deltaTime) const;
		void Reset() const;
		void Finalize();

		void AddActionListener(std::wstring_view actionName, DSH::Input::Trigger::Event event, const std::function<void(DSH::Input::Value value)>& listener) override;
		DSH::Input::IMappingContext* GetMappingContext() override;
		DSH::Input::Device::IKeyboard* GetKeyboard() override;
		DSH::Input::ISystem* GetSystem() override;

	private:
		DSH::Input::ISystem* _system;
		DSH::Input::IMappingContext* _mappingContext;

		DSH::Input::Device::IKeyboard* _keyboard;
		DSH::Input::Device::IMouse* _mouse;
	};
}