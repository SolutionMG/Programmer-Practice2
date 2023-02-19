

#ifndef DEFINE_H
#define DEFINE_H


namespace RenderMessageMacro
{
	///LOGIN
	constexpr char ACCESSMESSAGE[] = "** �ȳ��ϼ���. �ؽ�Ʈ ä�� ���� Ver 0.1�Դϴ�.\n\r";
	constexpr char LOGONREQUEST[] = "** �α��� ��ɾ�(LOGIN)�� ������ּ���. ex)LOGIN  [�̸�]\n\r";
	constexpr char LOGONFAILED[] = "** ���̵� �̹� ������Դϴ�. �ٸ� ���̵� ������ּ���.\n\r";
	constexpr char SUCCESSLOGONMESSAGE[] = "�ݰ����ϴ�. �ؽ�Ʈ ä�� ���� ver 0.1�Դϴ�.\n\r�̿��� �����Ͻ� ���� ������ �Ʒ� �̸��Ϸ� ���� �ٶ��ϴ�.\n\r�����մϴ�.\n\r\n\remail:jieun.kim23@nm-neo.com\n\r";

	///LINE, COMMANDLINE
	constexpr char ROOMINFOLINEMESSAGE[] = "-------------------------------��ȭ�� ����-------------------------------\n\r";
	constexpr char DIVIDELINEMESSAGE[] = "-------------------------------------------------------------------------\n\r";
	constexpr char COMMANDWAITMESSAGE[] = ">>";
	constexpr char SELECTCOMMANDMESSAGE[] = "��ɾ� �ȳ�(H) ����(X)\n\r";
	constexpr char NOCOMMANDMESSAGE[] = "��ϵ��� ���� ��ɾ� �Դϴ�.H�� ������ ��ɾ Ȯ���Ͻ� �� �ֽ��ϴ�. \n\r";

	///COMMAND
	constexpr char GUIDEMESSAGE[] = 
		"[H]				- ��ɾ� ��� �ȳ�\n\r[US]				- ���� ���� ���\n\r[LT]				- ��ȭ�� ���\n\r[O] [�ִ��ο�] [������]		- ��ȭ�� ����\n\r[J] [���ȣ]			- ��ȭ�� ����\n\r[PF] [�����̸�]			- �̿��� ���� ����\n\r[ST] [���ȣ]			- ��ȭ�� ���� ����\n\r[TO] [����ID] [�޽���]	- ���� ������\n\r[X]				- ��������\n\r";
	constexpr char FAILEDCOMMANDMESSAGE[] = "** ��Ŀ� �´� �޽����� ����� �ּ���.\n\r";
	constexpr char CREATEROOMFAILEDMESSAGE[] = "** �̹� ������ �̸��� ���� �����մϴ�. �ٸ� �̸��� ������ּ���.\n\r";
	constexpr char CREATEROOMFAILEDOVERUSERS[] = "** [�ּ� �ο�: 2��, �ִ� �ο�: 20��]\n\r";
	constexpr char CREATEROOMSUCCESSMESSAGE[] = "** ��ȭ���� �����Ǿ����ϴ�.\n\r";
	constexpr char ROOMENTERFAILEDMESSAGE[] = "** �������� �ʴ� ���Դϴ�. �ùٸ� �� ��ȣ�� �Է����ּ���.\n\r";
	constexpr char ROOMENTERFULLMESSAGE[] = "** �ش� ���� �̹� �ִ� �ο��Դϴ�. �ٸ� ���� �̿����ּ���.\n\r";
	constexpr char ROOMENTERNONAMEMESSAGE[] = "** ���� �̸��� �������� �ʽ��ϴ�. �ùٸ� �� �̸��� �Է����ּ���.\n\r";
	constexpr char USERINFOMESSAGEFAILED[] = "�������� �ʴ� �����Դϴ�.\n\r";
}


namespace CommandMessage
{
	constexpr char LOGON[] = "LOGIN";			//�α��� ��ɾ�

	constexpr char COMMANDLIST[] = "H";			//��ɾ� �ȳ�

	constexpr char USERLIST[] = "US";			//�̿��� ��� ����

	constexpr char ROOMLIST[] = "LT";			//��ȭ�� ��� ����

	constexpr char ROOMINFO[] = "ST";			//�� ���� ����

	constexpr char PLAYERINFO[] = "PF";			//�̿��� ���� ���� 

	constexpr char SECRETMESSAGE[] = "TO";		//�ӼӸ�

	constexpr char ROOMCREATE[] = "O";			//�����

	constexpr char ROOMENTER[] = "J";			//������

	constexpr char EXIT[] = "X";				//����

	constexpr char ROOMEXIT[] = "/X";			//�� ������
}
#endif // !DEFINE_H
