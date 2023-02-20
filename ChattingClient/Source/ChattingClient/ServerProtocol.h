#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

/// 값 초기화

namespace InitializeServer
{
	constexpr unsigned short TOTALCORE = 8;
	constexpr unsigned short SERVERPORT = 9000;
	constexpr unsigned short MAX_BUFFERSIZE = 1024;
	constexpr unsigned short MAX_PACKETSIZE = 255;
};


namespace InitializePlayer
{
	constexpr unsigned short MAX_NAME = 32;
}


namespace InitializeRoom
{
	constexpr unsigned short MAX_ROOMPLAYER = 20;
	constexpr unsigned short MIN_ROOMPLAYER = 2;
	constexpr unsigned short MAX_ROOMNAME = 32;
}


/// Login Packet
namespace PacketTypes
{
	constexpr short LOGIN = 0;
}

//#pragma pack(push, 1)
//struct Packet_Information
//{
//	unsigned char size;
//	int type;
//};
//
//struct Packet_Login_Request
//{
//	Packet_Information info;
//	char name[ InitializePlayer::MAX_NAME ];
//};
//
//struct Packet_Login_Answer
//{
//	Packet_Information info;
//	bool isAvailable;
//};
//#pragma pack(pop)

#endif // !SERVER_PROTOCOL_H
