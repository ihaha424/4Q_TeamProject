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
		class ChordAction final : public IChordAction
		{
		public:
			using OnTriggered = std::function<void(Event, Value)>;

			ChordAction();
			~ChordAction() override;

			HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
			ULONG AddRef() override;
			ULONG Release() override;

			void SetComponent(Component::IComponent* component) override;

			void AddModifier(Modifier::IModifier* modifier) override;

			void Update();

			void BindOnTriggered(const OnTriggered& onTriggered);

			void SetPrecedingAction(IAction* precedingAction) override;

		private:
			ULONG _referenceCount;
			Component::IComponent* _component;
			IAction* _precedingAction;
			bool _isDown;
			OnTriggered _onTriggered;
			std::vector <Modifier::IModifier*> _modifiers;
		};
	}
}
