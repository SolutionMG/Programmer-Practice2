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

namespace RenderMessageMacro
{
	///LOGIN
	constexpr char ACCESS_MESSAGE[] = "** 안녕하세요. 텍스트 채팅 서버 Ver 0.1입니다.\n\r";
	constexpr char LOGON_REQUEST[] = "** 로그인 명령어(LOGIN)을 사용해주세요. ex)LOGIN  [이름]\n\r";
	constexpr char LOGON_FAILED[] = "** <로그인 실패>아이디를 이미 사용중입니다. 다른 아이디를 사용해주세요.\n\r";
	constexpr char SUCCESS_LOGON_MESSAGE[] = "<로그인 성공> 반갑습니다. 텍스트 채팅 서버 ver 0.1입니다.\n\r이용중 불편하신 점이 있으면 아래 이메일로 문의 바랍니다.\n\r감사합니다.\n\r\n\remail:jieun.kim23@nm-neo.com\n\r";

	///LINE, COMMANDLINE
	constexpr char ROOMINFO_LINE_MESSAGE[] = "-------------------------------대화방 정보-------------------------------\n\r";
	constexpr char DIVIDE_LINE_MESSAGE[] = "-------------------------------------------------------------------------\n\r";
	constexpr char COMMAND_WAIT_MESSAGE[] = ">>";
	constexpr char SELECT_COMMAND_MESSAGE[] = "명령어 안내(H) 종료(X)\n\r";
	constexpr char NOCOMMAND_MESSAGE[] = "등록되지 않은 명령어 입니다.H를 누르면 명령어를 확인하실 수 있습니다. \n\r";

	///COMMAND
	constexpr char GUIDE_MESSAGE[] =
		"<명령어 안내>\n\r[H]				- 명령어 목록 안내\n\r[US]				- 접속 유저 목록\n\r[LT]				- 대화방 목록\n\r[O] [최대인원] [방제목]		- 대화방 생성\n\r[J] [방번호]			- 대화방 입장\n\r[PF] [유저이름]			- 이용자 정보 보기\n\r[ST] [방번호]			- 대화방 정보 보기\n\r[TO] [상대방ID] [메시지]	- 쪽지 보내기\n\r[X]				- 접속종료\n\r";
	constexpr char FAILED_COMMAND_MESSAGE[] = "** 양식에 맞는 메시지를 사용해 주세요.\n\r";
	constexpr char CREATE_ROOM_FAILED_OVERUSERS[] = "** <방 생성 실패>[최소 인원: 2명, 최대 인원: 20명]\n\r";
	constexpr char CREATE_ROOM_SUCCESS_MESSAGE[] = "** <방 생성> 대화방이 개설되었습니다.\n\r";
	constexpr char ROOM_ENTER_FAILED_MESSAGE[] = "** 존재하지 않는 방입니다. 올바른 방 번호를 입력해주세요.\n\r";
	constexpr char ROOM_ENTER_FULLMESSAGE[] = "** 해당 방은 이미 최대 인원입니다. 다른 방을 이용해주세요.\n\r";
	constexpr char ROOM_ENTER_NONAME_MESSAGE[] = "** 방의 이름이 존재하지 않습니다. 올바른 방 이름을 입력해주세요.\n\r";
	constexpr char USERINFO_MESSAGE_FAILED[] = "존재하지 않는 유저입니다.\n\r";
}

namespace SearchMacro
{
	///LOGIN
	TCHAR SEARCH_SUCCESS_LOGON[] = L"<로그인 성공>";
	TCHAR SEARCH_FAILED_LOGON[] = L"<로그인 실패>";

	///COMMAND
	TCHAR SEARCH_GUIDE[] = L"<명령어 안내>";
	TCHAR ROOM_CREATE[ ] = L"<방 생성>";
	TCHAR ROOM_CREATE_FAILED[] = L"<방 생성 실패>";

	TCHAR USER_LIST[] = L"유저 목록";
	TCHAR ROOM_LIST[] = L"방 목록";
}

/// Login Packet
//namespace PacketTypes
//{
//	constexpr short LOGIN = 0;
//}

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
