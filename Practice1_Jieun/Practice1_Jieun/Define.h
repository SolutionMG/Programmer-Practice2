

#ifndef DEFINE_H
#define DEFINE_H


namespace RenderMessageMacro
{
	///LOGIN
	constexpr char ACCESSMESSAGE[] = "** 안녕하세요. 텍스트 채팅 서버 Ver 0.1입니다.\n\r";
	constexpr char LOGONREQUEST[] = "** 로그인 명령어(LOGIN)을 사용해주세요. ex)LOGIN  [이름]\n\r";
	constexpr char LOGONFAILED[] = "** 아이디를 이미 사용중입니다. 다른 아이디를 사용해주세요.\n\r";
	constexpr char SUCCESSLOGONMESSAGE[] = "반갑습니다. 텍스트 채팅 서버 ver 0.1입니다.\n\r이용중 불편하신 점이 있으면 아래 이메일로 문의 바랍니다.\n\r감사합니다.\n\r\n\remail:jieun.kim23@nm-neo.com\n\r";

	///LINE, COMMANDLINE
	constexpr char ROOMINFOLINEMESSAGE[] = "-------------------------------대화방 정보-------------------------------\n\r";
	constexpr char DIVIDELINEMESSAGE[] = "-------------------------------------------------------------------------\n\r";
	constexpr char COMMANDWAITMESSAGE[] = ">>";
	constexpr char SELECTCOMMANDMESSAGE[] = "명령어 안내(H) 종료(X)\n\r";
	constexpr char NOCOMMANDMESSAGE[] = "등록되지 않은 명령어 입니다.H를 누르면 명령어를 확인하실 수 있습니다. \n\r";

	///COMMAND
	constexpr char GUIDEMESSAGE[] = 
		"[H]				- 명령어 목록 안내\n\r[US]				- 접속 유저 목록\n\r[LT]				- 대화방 목록\n\r[O] [최대인원] [방제목]		- 대화방 생성\n\r[J] [방번호]			- 대화방 입장\n\r[PF] [유저이름]			- 이용자 정보 보기\n\r[ST] [방번호]			- 대화방 정보 보기\n\r[TO] [상대방ID] [메시지]	- 쪽지 보내기\n\r[X]				- 접속종료\n\r";
	constexpr char FAILEDCOMMANDMESSAGE[] = "** 양식에 맞는 메시지를 사용해 주세요.\n\r";
	constexpr char CREATEROOMFAILEDMESSAGE[] = "** 이미 동일한 이름의 방이 존재합니다. 다른 이름을 사용해주세요.\n\r";
	constexpr char CREATEROOMFAILEDOVERUSERS[] = "** [최소 인원: 2명, 최대 인원: 20명]\n\r";
	constexpr char CREATEROOMSUCCESSMESSAGE[] = "** 대화방이 개설되었습니다.\n\r";
	constexpr char ROOMENTERFAILEDMESSAGE[] = "** 존재하지 않는 방입니다. 올바른 방 번호를 입력해주세요.\n\r";
	constexpr char ROOMENTERFULLMESSAGE[] = "** 해당 방은 이미 최대 인원입니다. 다른 방을 이용해주세요.\n\r";
	constexpr char ROOMENTERNONAMEMESSAGE[] = "** 방의 이름이 존재하지 않습니다. 올바른 방 이름을 입력해주세요.\n\r";
	constexpr char USERINFOMESSAGEFAILED[] = "존재하지 않는 유저입니다.\n\r";
}


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
