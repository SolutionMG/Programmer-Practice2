// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerManager.h"
#include "ServerProtocol.h"


void UServerManager::Init()
{
}

void UServerManager::Shutdown( )
{
	closesocket( m_socket );
	WSACleanup( );
}

bool UServerManager::ConnectToServer()
{
	WSADATA wsaData;
	int returnValue = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	if (returnValue != 0)
	{
		UE_LOG( LogTemp, Warning, TEXT( "WSAStartup Failed" ) );
		return false;
	}

	returnValue = CreateSocket();
	if (returnValue != 0)
	{
		UE_LOG( LogTemp, Warning, TEXT( "CreateSocket Failed" ) );
		return false;
	}

	ZeroMemory( &m_sockAddr, sizeof( m_sockAddr ) );
	m_sockAddr.sin_family = AF_INET;
	m_sockAddr.sin_port = htons( InitializeServer::SERVERPORT );
	inet_pton( AF_INET, SERVERIP, &m_sockAddr.sin_addr );

	///논블로킹으로 소켓 connect 요청
	///select를 사용하여 connect의  timeout 5초 부여  
	returnValue = connect( m_socket, ( sockaddr FAR* ) & m_sockAddr, sizeof( m_sockAddr ) );

	if (returnValue != 0)
	{
		int error = WSAGetLastError();
		if (error != EINPROGRESS && errno != EWOULDBLOCK && error != WSAEWOULDBLOCK)
		{
			UE_LOG( LogTemp, Warning, TEXT( "connect Failed" ) );
			return false;
		}

		fd_set readSet, writeSet;
		FD_ZERO( &readSet );
		///5초 동안 기다리기 - 연결여부 확인, 연결이 되었으면 즉시 종료
		timeval timeOut = { 5, 0 };
		FD_SET( m_socket, &readSet );
		writeSet = readSet;

		returnValue = select( 1, &readSet, &writeSet, NULL, &timeOut );

		if (returnValue <= 0)
		{
			UE_LOG( LogTemp, Warning, TEXT( "select / connect time out" ) );
			return false;
		}

		error = 0;
		socklen_t length = sizeof( error );
		if (getsockopt( m_socket, SOL_SOCKET, SO_ERROR, ( char* )&error, &length ) < 0 || error != 0)
		{
			UE_LOG( LogTemp, Warning, TEXT( "select / connect time out" ) );
			return false;
		}

	}
	return true;
}

int UServerManager::CreateSocket()
{
	m_socket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, 0 );
	if (m_socket == INVALID_SOCKET)
	{
		UE_LOG( LogTemp, Warning, TEXT( "WSASocket Failed" ) );
		return -1;
	}

	//non block
	unsigned long noblock = 1;
	int returnValue = ioctlsocket( m_socket, FIONBIO, &noblock );
	if (returnValue != 0)
	{
		UE_LOG( LogTemp, Warning, TEXT( "ioctlsocket Failed" ) );
		return -1;
	}

	//nagle off
	int socketOption = 1;
	returnValue = setsockopt( m_socket, SOL_SOCKET, TCP_NODELAY, reinterpret_cast< const char* >( &socketOption ), sizeof( socketOption ) );
	if (returnValue != 0)
	{
		UE_LOG( LogTemp, Warning, TEXT( "ioctlsocket Failed" ) );
		return -1;
	}

	return 0;
}

void UServerManager::SendPacket( int32 type, const FString& packet )
{

	if ( packet.IsEmpty( ) )
		return;

	switch ( type )
	{
	case PacketTypes::LOGIN:
	{
		if ( packet.Len( ) > 32 )
		{
			UE_LOG( LogTemp, Warning, TEXT( "최대 이름길이 초과 Failed" ) );
			return;
		}

		Packet_Login_Request format;
		format.info.size = sizeof( Packet_Login_Request );
		format.info.type = PacketTypes::LOGIN;
	
		const wchar_t* encode = *packet;
		char defaultSetting = '?';
		WideCharToMultiByte( CP_ACP, 0, encode, -1, format.name, 32, &defaultSetting, NULL );

		send( m_socket, reinterpret_cast< char* >( &format ), format.info.size, 0 );
		
	}
	break;
	default:
	break;
	}

}

void UServerManager::ReceivePacket( )
{
	char buf[ InitializeServer::MAX_BUFFERSIZE ];
	char* packet = buf;
	int received = 0;
	int left = 2; // 처음에 size, type를 미리 받기 위함

	bool init_come = true;

	while ( left > 0 || init_come )
	{
		received = recv( m_socket, packet, left, 0 );
		if ( received == SOCKET_ERROR )//에러 발생
			return;
		else if ( received == 0 ) //받은게 없음
			break;

		if ( init_come )
		{
			left = buf[ 0 ] - received;
			packet += received;
			init_come = false;
		}
		else
		{
			left -= received;
			packet += received;

			if ( left == 0 ) {
				//Process_Packet( buf );
				return;
			}
		}
	}
}