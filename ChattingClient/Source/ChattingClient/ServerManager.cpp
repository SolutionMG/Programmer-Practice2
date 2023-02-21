// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerManager.h"
#include "ServerProtocol.h"

void UServerManager::Init()
{
	m_encodingBuffer = "";
}

void UServerManager::Shutdown( )
{
	if ( m_socket != nullptr)
		m_socket->Close();
}

bool UServerManager::ConnectToServer()
{
	m_socket = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateSocket( NAME_Stream, TEXT( "default" ) );
	if ( !m_socket )
		return false;


	FIPv4Address ip;
	if ( !FIPv4Address::Parse( SERVERIP, ip ) )
		return false;

	TSharedRef<FInternetAddr> address = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateInternetAddr( );
	address->SetIp( ip.Value );
	address->SetPort( InitializeServer::SERVERPORT );

	bool connect = m_socket->Connect( *address );
	m_socket->SetNonBlocking( true );
	m_socket->SetNoDelay( true );

	return true;
}

/*
void UServerManager::SendPacket( int32 type, const FString& packet )
{

	//if ( packet.IsEmpty( ) )
	//	return;

	/*switch ( type )
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
*/

bool UServerManager::SendPacket(const FString& packet)
{
	if ( !m_socket )
		return false;

	FString packetEnd = packet;
	packetEnd += "\n";
	char message[InitializeServer::MAX_BUFFERSIZE];
	const wchar_t* encode = *packetEnd;
	char defaultSetting = '?';
	
	int32 len = WideCharToMultiByte( CP_ACP, 0, encode, -1, NULL, 0 , NULL , NULL );
	WideCharToMultiByte(CP_ACP, 0, encode, -1, message, len, &defaultSetting, NULL);
	int32 bytesSents = 0;

	return m_socket->Send( ( uint8* ) ( message ), len, bytesSents );
}

bool UServerManager::ReceivePacket( )
{
	if ( !m_socket )
		return false;

	char buf[ InitializeServer::MAX_BUFFERSIZE ] = { NULL, };
	int32 bytesSents = 0;
	FString encode;

	bool returnValue = m_socket->Recv( ( uint8* ) ( buf ), InitializeServer::MAX_BUFFERSIZE - 1, bytesSents );
	if ( !returnValue )
	{
		return false;
	}
	///받은 데이터 없음
	else if ( bytesSents == 0 )
	{
		return true;
	}

	wchar_t encodebuf[ InitializeServer::MAX_BUFFERSIZE ] = {NULL, };
	int32 len = MultiByteToWideChar( CP_ACP, 0, buf, strlen( buf ) , NULL, NULL );
	MultiByteToWideChar( CP_ACP, 0, buf, strlen( buf ) , encodebuf, len );

	for ( int32 i = 0; i <= len; ++i )
	{
		if ( encodebuf[ i ] == '\0' )
		{
			ProcessPacket( m_encodingBuffer );
			m_encodingBuffer = "";
		}
		else
		{
			m_encodingBuffer += encodebuf[ i ];
		}
	}

	return true;
}

bool UServerManager::ProcessPacket( const FString& packet )
{
	//	UE_LOG( LogTemp, Warning, TEXT("%s"), *packet);
	if ( packet.Contains(SearchMacro::SEARCH_SUCCESS_LOGON) )
	{
		return true;
	}


	return false;
}
