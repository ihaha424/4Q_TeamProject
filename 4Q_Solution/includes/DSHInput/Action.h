#pragma once
#include "Value.h"

namespace DSH::Input
{
	namespace Trigger
	{
		enum class Event : unsigned char;
		class Down;
		class ChordAction;
	}

	class Action final : public IAction
	{
	public:
		Action();
		~Action() override;

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		void Update(float deltaTime);
		void Reset();

		void AddListener(Trigger::Event event, Listener listener) override;

		HRESULT GetTrigger(Trigger::IDown** ppDown) override;
		HRESULT GetTrigger(Trigger::IChordAction** ppChordAction) override;

		bool IsTriggered() override;

	private:
		void OnTriggered(Trigger::Event event, Value value);

		ULONG _referenceCount;

		std::vector<Trigger::Down*> _downs;
		std::vector<Trigger::ChordAction*> _chordActions;

		bool _isTriggered;
		Trigger::Event _event;
		Value _value;

		std::unordered_map<Trigger::Event, std::vector<Listener>> _listeners;
	};
}
