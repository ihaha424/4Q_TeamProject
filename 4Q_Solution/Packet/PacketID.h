#pragma once

enum class PacketID : short {
	Default = 0,

	// Connect
	EnterRequest,
	EnterAccept,
	EnterReject,
	Exit,
	ExitOk,

	// Sync To Client
	Sync,
	ObjectSync,
	MoveSync,

	// Play Logic
	Move,
	Jump,
	StateChange,
	ObjectMove,
	PickObject,
	PutObject,
	PuzzleSuccess,
	SoundPlay,
	InteractObject,
	PlayDialog,
	InteraceDialog,
	QuestStart,
	QuestClear,

	// Data Transfer
	DataSendComplete,
	DataRequest,
	DataRemote,
	DataObject,

};