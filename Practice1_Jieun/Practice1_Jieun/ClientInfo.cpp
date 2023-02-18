

#include "pch.h"
#include "ClientInfo.h"


ClientInfo::ClientInfo() : m_socket{ INVALID_SOCKET }, m_over{ WSAOVERLAPPED_EXTEND() }, m_state{ EClientState::END }
{
	ZeroMemory(&m_over, sizeof(m_over));
	m_over.wsaBuffer.buf = m_over.networkBuffer;
	m_over.wsaBuffer.len = InitailizeServer::MAX_BUFFERSIZE;
}

ClientInfo::~ClientInfo() noexcept = default;

void ClientInfo::ReceivePacket()
{
	/// Overlapped Receive 요청
	m_receiveLock.lock();
	ZeroMemory(&m_over, sizeof(m_over));
	m_over.wsaBuffer.buf = m_over.networkBuffer;
	m_over.wsaBuffer.len = InitailizeServer::MAX_BUFFERSIZE;
	m_over.opType = EOperationType::RECV;
	DWORD flag = 0;
	WSARecv(m_socket, &m_over.wsaBuffer, 1, NULL, &flag, &m_over.over, NULL);
	m_receiveLock.unlock();
}

void ClientInfo::SendPacket( const std::string_view& data )
{
	/// Overlapped Send 요청
	WSAOVERLAPPED_EXTEND* over = new WSAOVERLAPPED_EXTEND;
	over->opType = EOperationType::SEND;
	ZeroMemory(&over->over, sizeof(over->over));
	memcpy_s(over->networkBuffer, sizeof(over->networkBuffer), data.data(), data.size() );
	over->wsaBuffer.buf = over->networkBuffer;
	over->wsaBuffer.len = static_cast< decltype( over->wsaBuffer.len ) >( data.size() );
	WSASend(m_socket, &over->wsaBuffer, 1, 0, 0, &over->over, 0);
}

void ClientInfo::StartLock()
{
	m_clientLock.lock();
}

void ClientInfo::EndLock()
{
	m_clientLock.unlock();
}

const SOCKET ClientInfo::GetSocket()
{
	return m_socket;
}

void ClientInfo::SetSocket( const SOCKET& s )
{
	m_socket = s;
}

const WSAOVERLAPPED_EXTEND& ClientInfo::GetOverlappedExtend()
{
	return m_over;
}

const EClientState& ClientInfo::GetState()const
{
	return m_state;
}

void ClientInfo::SetOverlappedExtend( const WSAOVERLAPPED_EXTEND& over )
{
	memcpy_s( &m_over, sizeof( m_over ), &over, sizeof( over ) );
}
void ClientInfo::SetOverlappedOperation( const EOperationType& operation )
{
	m_over.opType = operation;
}

void ClientInfo::SetState( const EClientState& state )
{
	m_state = state;
}

