

#ifndef CLIENT_H
#define CLIENT_H


enum class EClientState : char
{
	ACCESS, LOGON, ROOM, EXIT, END
};

class ClientInfo
{
private:
	SOCKET m_socket;
	WSAOVERLAPPED_EXTEND m_over;
	EClientState m_state;

	unsigned char m_previousReceivePosition;

	///Lock
	std::mutex m_clientLock;
	std::mutex m_receiveLock;

public:
	explicit ClientInfo();
	virtual ~ClientInfo() noexcept;

	///Set
	void SetSocket( const SOCKET& s );
	void SetOverlappedExtend( const WSAOVERLAPPED_EXTEND& over );
	void SetOverlappedOperation( const EOperationType& operation );
	void SetState( const EClientState& state );
	void SetPreviousReceivePosition( const unsigned char& position );

	///Get 
	const SOCKET GetSocket();
	const WSAOVERLAPPED_EXTEND& GetOverlappedExtend();
	const EClientState& GetState() const;
	const unsigned char& GetPreviousReceivePosition( );

	///패킷 송수신 요청 (Overlapped)
	void ReceivePacket();
	void SendPacket(const std::string_view& data);

	///Lock
	void StartLock();
	void EndLock();
	std::mutex& GetLock();
};
#endif // !CLIENT_H

