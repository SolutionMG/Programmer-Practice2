#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

/// �� �ʱ�ȭ

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
	constexpr char ACCESS_MESSAGE[] = "** �ȳ��ϼ���. �ؽ�Ʈ ä�� ���� Ver 0.1�Դϴ�.\n\r";
	constexpr char LOGON_REQUEST[] = "** �α��� ��ɾ�(LOGIN)�� ������ּ���. ex)LOGIN  [�̸�]\n\r";
	constexpr char LOGON_FAILED[] = "** <�α��� ����>���̵� �̹� ������Դϴ�. �ٸ� ���̵� ������ּ���.\n\r";
	constexpr char SUCCESS_LOGON_MESSAGE[] = "<�α��� ����> �ݰ����ϴ�. �ؽ�Ʈ ä�� ���� ver 0.1�Դϴ�.\n\r�̿��� �����Ͻ� ���� ������ �Ʒ� �̸��Ϸ� ���� �ٶ��ϴ�.\n\r�����մϴ�.\n\r\n\remail:jieun.kim23@nm-neo.com\n\r";

	///LINE, COMMANDLINE
	constexpr char ROOMINFO_LINE_MESSAGE[] = "-------------------------------��ȭ�� ����-------------------------------\n\r";
	constexpr char DIVIDE_LINE_MESSAGE[] = "-------------------------------------------------------------------------\n\r";
	constexpr char COMMAND_WAIT_MESSAGE[] = ">>";
	constexpr char SELECT_COMMAND_MESSAGE[] = "��ɾ� �ȳ�(H) ����(X)\n\r";
	constexpr char NOCOMMAND_MESSAGE[] = "��ϵ��� ���� ��ɾ� �Դϴ�.H�� ������ ��ɾ Ȯ���Ͻ� �� �ֽ��ϴ�. \n\r";

	///COMMAND
	constexpr char GUIDE_MESSAGE[] =
		"<��ɾ� �ȳ�>\n\r[H]				- ��ɾ� ��� �ȳ�\n\r[US]				- ���� ���� ���\n\r[LT]				- ��ȭ�� ���\n\r[O] [�ִ��ο�] [������]		- ��ȭ�� ����\n\r[J] [���ȣ]			- ��ȭ�� ����\n\r[PF] [�����̸�]			- �̿��� ���� ����\n\r[ST] [���ȣ]			- ��ȭ�� ���� ����\n\r[TO] [����ID] [�޽���]	- ���� ������\n\r[X]				- ��������\n\r";
	constexpr char FAILED_COMMAND_MESSAGE[] = "** ��Ŀ� �´� �޽����� ����� �ּ���.\n\r";
	constexpr char CREATE_ROOM_FAILED_MESSAGE[] = "** �̹� ������ �̸��� ���� �����մϴ�. �ٸ� �̸��� ������ּ���.\n\r";
	constexpr char CREATE_ROOM_FAILED_OVERUSERS[] = "** [�ּ� �ο�: 2��, �ִ� �ο�: 20��]\n\r";
	constexpr char CREATE_ROOM_SUCCESS_MESSAGE[] = "** ��ȭ���� �����Ǿ����ϴ�.\n\r";
	constexpr char ROOM_ENTER_FAILED_MESSAGE[] = "** �������� �ʴ� ���Դϴ�. �ùٸ� �� ��ȣ�� �Է����ּ���.\n\r";
	constexpr char ROOM_ENTER_FULLMESSAGE[] = "** �ش� ���� �̹� �ִ� �ο��Դϴ�. �ٸ� ���� �̿����ּ���.\n\r";
	constexpr char ROOM_ENTER_NONAME_MESSAGE[] = "** ���� �̸��� �������� �ʽ��ϴ�. �ùٸ� �� �̸��� �Է����ּ���.\n\r";
	constexpr char USERINFO_MESSAGE_FAILED[] = "�������� �ʴ� �����Դϴ�.\n\r";
}
namespace SearchMacro
{
	///LOGIN
	constexpr char SEARCH_SUCCESS_LOGON[ ] = "<�α��� ����>";
	constexpr char SEARCH_FAILED_LOGON[ ] = "<�α��� ����>";

	///COMMAND
	constexpr char SEARCH_GUIDE[ ] = "<��ɾ� �ȳ�>";
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
