

#ifndef DEFINE_H
#define DEFINE_H

namespace CommandMessage
{
	constexpr char LOGON[] = "LOGIN";			//로그인 명령어

	constexpr char COMMANDLIST[] = "H";			//명령어 안내

	constexpr char USERLIST[] = "US";			//이용자 목록 보기

	constexpr char ROOMLIST[] = "LT";			//대화방 목록 보기

	constexpr char ROOMINFO[] = "ST";			//방 정보 보기

	constexpr char PLAYERINFO[] = "PF";			//이용자 정보 보기 

	constexpr char SECRETMESSAGE[] = "TO";		//귓속말

	constexpr char ROOMCREATE[] = "O";			//방생성

	constexpr char ROOMENTER[] = "J";			//방입장

	constexpr char EXIT[] = "X";				//종료

	constexpr char ROOMEXIT[] = "/X";			//방 나가기
}

#endif // !DEFINE_H
