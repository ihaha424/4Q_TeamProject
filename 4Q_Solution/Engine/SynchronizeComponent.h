#pragma once

namespace Engine::Component
{
	class SynchronizeComponent : public Component, public Network::Terminal
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
		SynchronizeComponent();

		void Initialize() override;
		void Finalize() override;

		void SetSerialNumber(int num);
		const int GetSerialNumber() const;
		void InvokeMessage(const Packet& packet);

		template <class C, class MsgType>
		void AddCallback(short packetId, void(C::* fn)(const MsgType*), C* receiver) {
			IDelegate* delegate = new Delegate<C, MsgType>(receiver, fn);
			_callbackMap.insert({ packetId, delegate });
		}

		void RemoveCallback(short packetId);


	private:
		int _serialNumber;
		CallbackMap _callbackMap;

	public:
		std::string _msgBuffer;

		ConnectMsg::EnterAccept _enterAccept;
		ConnectMsg::Exit Exit;
		ConnectMsg::SetRoomMaster _setRoomMaster;
		ConnectMsg::SyncPlayer _syncPlayer;

		MoveMsg::Move _move;
		MoveMsg::Jump _jump;
		MoveMsg::MoveSync _moveSync;
		MoveMsg::StateChange _stateChange;

		PlayMsg::SelectPart _selectPart;
		PlayMsg::InteractDialog _interactDialog;
		PlayMsg::DialogProgress _dialogProgress;
	};

}
