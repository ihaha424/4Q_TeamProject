#pragma once

namespace DSH::Input
{
	namespace Component
	{
		struct IComponent;
	}

	namespace Modifier
	{
		struct IModifier;
	}

	namespace Trigger
	{
		class Down final : public IDown
		{
		public:
			using OnTriggered = std::function<void(Event, Value)>;

			Down();
			~Down() override;

			HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
			ULONG AddRef() override;
			ULONG Release() override;

			void SetComponent(Component::IComponent* component) override;

			void AddModifier(Modifier::IModifier* modifier) override;

			void Update();

			void BindOnTriggered(const OnTriggered& onTriggered);

		private:
			ULONG _referenceCount;
			Component::IComponent* _component;
			bool _isDown;
			OnTriggered _onTriggered;
			std::vector <Modifier::IModifier*> _modifiers;
		};
	}
}
