#pragma once

enum class PacketID : short {
	Default = 0,
	EnterRequest,
	EnterAccept,
	EnterReject,
	Exit,
	ExitOk,
	Sync,
	Move,
	Jump,
	SelectPart,
	DialogOpen,
	DialogNext,


};