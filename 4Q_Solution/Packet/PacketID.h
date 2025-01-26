#pragma once

enum class PacketID : short {
	Default = 0,
	EnterRequest,
	EnterAccept,
	EnterReject,
	Exit,
	ExitOk,
	Sync,
	MoveSync,
	Move,
	Jump,
	SelectPart,
	DialogOpen,
	DialogNext,
	StateChange,


};