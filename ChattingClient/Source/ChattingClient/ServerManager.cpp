// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerManager.h"


#define SERVERPORT 9000


void UServerManager::Init()
{
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
	m_sockAddr.sin_port = htons( SERVERPORT );
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
		///5초 동안 기다리기 - 연결여부 확인
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

