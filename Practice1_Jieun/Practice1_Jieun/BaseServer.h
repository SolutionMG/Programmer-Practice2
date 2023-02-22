

#ifndef BASESERVER_H
#define BASESERVER_H
#include <functional>


class PlayerInfo;
class ChattingRoom;

class BaseServer final
{
private:
	SOCKET m_listenSocket;
	HANDLE m_iocpHandle;

	///�÷��̾� ������ ����
	std::mutex m_playersLock;
	std::unordered_map<SOCKET, PlayerInfo> m_players;

	///Ŀ�ǵ� �� �Լ� ������ ����
	std::unordered_map<std::string, std::function<bool(const SOCKET& socket)>> m_commandFunctions;

	///ä�ù� ������ ����
	std::mutex m_chattRoomLock;
	std::unordered_map<int, ChattingRoom> m_chattingRooms;

	///ä�ù� ��ȣ ������ ����
	std::mutex m_chattRoomNumLock;
	std::priority_queue<int, std::vector<int>, std::greater<int> > m_charRoomNumber;

	///�α׿� ���μ���
	std::mutex m_logOnLock;
	std::queue<SOCKET> m_logOn;

public:
	explicit BaseServer();
	virtual ~BaseServer() noexcept;

	bool Initialize();
	bool Listen();
	bool OpenServer();

private:
	/// ���� IOCP ���μ��� (Accept, Recv, Send)
	bool MainWorkProcess();

	/// �÷��̾� ���� ó�� �Լ�
	bool Accept(WSAOVERLAPPED_EXTEND* over);
	bool AddNewClient(const SOCKET& socket);

	///�ڳ� Ŭ���̾�Ʈ�κ��� ���� ��Ŷ ������
	bool ReassemblePacket( char* packet, const DWORD& bytes, const SOCKET& socket );
	bool Disconnect(SOCKET socket);

	///�÷��̾� ���¿� ���� ��Ŷ ��� ����
	bool StateWorkBranch( const SOCKET& socket, const std::string& command );

	/// �÷��̾��� ��ɾ ���� ��Ŷ ��� ����
	bool CommandWorkBranch( const SOCKET& socket, const std::string& command );

	/// �÷��̾� Ŀ�ǵ� �Լ���...
	void AddCommand(const std::string& command, std::function<bool( const SOCKET& socket ) > commandFunction );

	bool InitializeCommandFunction();
	bool ReqeustCommandList(const SOCKET& socket);
	bool RequestExit( const SOCKET& socket );

	bool RequestRoomCreate( const SOCKET& socket );
	bool RequestRoomEnter( const SOCKET& socket );
	bool RequestRoomList( const SOCKET& socket );
	bool RequestRoomInfo( const SOCKET& socket );

	bool RequestUserList( const SOCKET& socket);
	bool RequestUserInfo( const SOCKET& socket);
	bool RequestNote( const SOCKET& socket);

	bool RequestRoomExit( const SOCKET& socket );

	/// �α׿� ���� ���μ���
	void LogOnCommandProcess();

	///ä�ù濡���� ��ȭ
	bool Chatting(const SOCKET& socket);

private:
	void DisplayError(const char* msg);
};
#endif // !BASESERV
