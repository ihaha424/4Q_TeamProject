#pragma once

enum class PacketID : unsigned short {
	Default = 0,
	EnterRequest,
	EnterAccept,
	Exit,
	Sync,
	Move,
	Jump,
	

};