#pragma once
#include "Server/ClientEntrance.h"	
#include "../Packet/ProtoInclude.h"
#include "../Packet/PacketID.h"

class IDelegate {
public:
	virtual void Invoke(const google::protobuf::Message* e) = 0;
};

template <class C, class E>
class Delegate : public IDelegate {
	typedef void(C::* Callback)(const E*);

public:
	Delegate(C* recver, Callback& fn) : _receiver(recver), _callback(fn) {}

	virtual void Invoke(const google::protobuf::Message* e) override {
		(_receiver->*_callback)(reinterpret_cast<const E*>(e));
	}

private:
	C* _receiver;
	Callback _callback;
};

class NetworkTemp
{
public:
	NetworkTemp() = default;

	bool Initialize();
	void Dispatch();

	template <class C, class Msg>
	inline void AddCallback(short packetId, void(C::* fn)(const Msg*), C* receiver) {
		if (packetId == (short)PacketID::EnterAccept) {
			acceptEnter = new Delegate<C, Msg>(receiver, fn);
		}
		else if (packetId == (short)PacketID::Move) {
			moveSync = new Delegate<C, Msg>(receiver, fn);
		}
		else if (packetId == (short)PacketID::Sync) {
			playerSync = new Delegate<C, Msg>(receiver, fn);
		}
	}

	void SendUpdate();

	//void(*moveSync)(const ConnectMsg::SyncPlayer*);
	//void(*acceptEnter)(const ConnectMsg::EnterAccept*);
	//void(*playerSync)(const ConnectMsg::SyncPlayer*);

	IDelegate* moveSync;
	IDelegate* acceptEnter;
	IDelegate* playerSync;

	static NetworkTemp* GetInstance() {
		if (_instance == nullptr) {
			_instance = new NetworkTemp();
		}
		return _instance;
	}

	static void DestroyInstance() {
		if (_instance) {
			delete _instance;
			_instance = nullptr;
		}
	}

private:
	PacketQueue* msgContainer = nullptr;

	static NetworkTemp* _instance;

	ConnectMsg::EnterAccept _enterAccept;
	ConnectMsg::Exit Exit;
	ConnectMsg::SetRoomMaster _setRoomMaster;
	ConnectMsg::SyncPlayer _syncPlayer;

	MoveMsg::Move _move;
	MoveMsg::Jump _jump;

	PlayMsg::SelectPart _selectPart;
	PlayMsg::InteractDialog _interactDialog;
	PlayMsg::DialogProgress _dialogProgress;
};


