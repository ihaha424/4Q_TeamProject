#pragma once

enum class PacketID : short {
	Default = 0,

	// Connect
	EnterRequest,
	EnterAccept,
	EnterReject,
	Exit,

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
	PuzzleStart,
	PuzzleSuccess,
	SoundPlay,
	InteractObject,
	TriggerObject,
	PlayDialog,
	InteractDialog,
	QuestStart,
	QuestClear,
	ObjectActive,
	ObjectDisable,
	DialogNext,

	// Data Transfer
	DataSendComplete,
	DataRequest,
	DataRemote,
	DataObject,

};