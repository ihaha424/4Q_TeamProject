#pragma once

namespace Engine::Component
{
	class Synchronize : public Component, public Network::Terminal
	{
		// TODO: Implement synchronization component
		class IDelegate {
		public:
			IDelegate() = default;
			virtual void Invoke(const google::protobuf::Message* msg) const = 0;
		};
		
		template <class C, class MsgType>
		class Delegate : public IDelegate {
			typedef void(C::* Callback)(const MsgType*);
		public:
			Delegate(C* receiver, Callback& fn) :
				_receiver(receiver), 
				_callback(fn)
			{}
			void Invoke(const google::protobuf::Message* msg) const override {
				(_receiver->*_callback)(reinterpret_cast<const MsgType*>(msg));
			}
		private:
			C* _receiver;
			Callback _callback;
		};

		using CallbackMap = std::unordered_map<short, IDelegate*>;

	public:
		Synchronize();

		void Initialize(const Modules& modules) override;
		void Finalize() override;

		void InvokeMessage(const Packet& packet) override;

		template <class C, class MsgType>
		void AddCallback(short packetId, void(C::* fn)(const MsgType*), C* receiver) {
			IDelegate* delegate = new Delegate<C, MsgType>(receiver, fn);
			_callbackMap.insert({ packetId, delegate });
		}

		void RemoveCallback(short packetId);


	private:
		CallbackMap _callbackMap;

	public:
		std::string _msgBuffer;

		ConnectMsg::EnterAccept _enterAccept;
		ConnectMsg::SyncPlayer _syncPlayer;
		ConnectMsg::SyncObject _syncObject;

		MoveMsg::Move _move;
		MoveMsg::Jump _jump;
		MoveMsg::MoveSync _moveSync;
		MoveMsg::StateChange _stateChange;
		MoveMsg::ObjectMove _objectMove;

		PlayMsg::SelectPart _selectPart;
		PlayMsg::PickObject _pickObject;
		PlayMsg::PutObject _putObject;
		PlayMsg::SoundPlay _soundPlay;

		PlayMsg::InteractDialog _interactDialog;
		PlayMsg::DialogProgress _dialogProgress;
	};

}
