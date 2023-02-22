// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerManager.h"
#include "ServerProtocol.h"
#include "ChattingGameMode.h"
#include "ChattingRoom_Widget.h"
#include "ShowUserList_Widget.h"
#include "ShowRoomList_Widget.h"
#include "ReceiveSecretMessage.h"
#include "RoomInfo_Widget.h"
#include "UserInfo_Widget.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


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

	if ( !connect )
		return false;

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
	AChattingGameMode* gameMode = Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	if ( !gameMode )
		return false;

	///UE_LOG( LogTemp, Warning, TEXT("%s"), *packet);	
	bool isChatting = Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld( ) ) )->GetisChattingRoom( );
	if ( isChatting )
	{
		UUserWidget* cur = Cast<UChattingRoom_Widget>( Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld( ) ) )->GetCurrentWidget( ) );
		if ( cur != nullptr )
			Cast<UChattingRoom_Widget>( cur )->AddChatLogWidget( packet );
	}

	else
	{

		if ( packet.Contains( FString( SearchMacro::SEARCH_SUCCESS_LOGON ) ) )
		{
			/// 로그인 성공 -> 로비로 이동
			FString path = "/Game/UserInterfaces/LobbyWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass( ) );
			gameMode->ChangeMenuWidget( widget );

			return true;
		}
		else if ( packet.Contains( SearchMacro::SEARCH_FAILED_LOGON ) )
		{
			/// 로그인 실패
			FString path = "/Game/UserInterfaces/LoginFailedWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass( ) );
			gameMode->CreateUIWidget( widget );

			return true;
		}
		else if ( packet.Contains( SearchMacro::ROOM_CREATE ) )
		{
			///방 생성 성공
			FString path = "/Game/UserInterfaces/ChattingRoomWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass( ) );
			gameMode->ChangeMenuWidget( widget );
			gameMode->SetisChattingRoom( true ); 
		}
		else if ( packet.Contains( SearchMacro::ROOM_CREATE_FAILED ) )
		{
			///방 생성 실패
			FString path = "/Game/UserInterfaces/RoomCreateFaileWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			gameMode->CreateUIWidget( widget );
		}
		else if ( packet.Contains( SearchMacro::USER_LIST ) )
		{
			///유저 목록
			FString path = "/Game/UserInterfaces/UseListWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			UUserWidget* UI = gameMode->CreateUIWidget( widget );

			if ( UI != nullptr )
				Cast<UShowUserList_Widget>( UI )->AddUserListWidget( packet );
		}
		else if ( packet.Contains( SearchMacro::ROOM_LIST ) )
		{
			///방 목록
			FString path = "/Game/UserInterfaces/RoomListWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			UUserWidget* UI = gameMode->CreateUIWidget( widget );

			if ( UI != nullptr )
				Cast<UShowRoomList_Widget>( UI )->AddRoomListWidget( packet );
		}

		else if ( packet.Contains(SearchMacro::SECRET_MESSAGE) )
		{
			FString path = "/Game/UserInterfaces/ReceiveSecretMessageWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			UUserWidget* UI = gameMode->CreateUIWidget( widget );

			if ( UI != nullptr )
				Cast<UReceiveSecretMessage>( UI )->SetMessage( packet );
		}
		else if ( packet.Contains( SearchMacro ::ROOM_ENTERFAILED ) )
		{
			FString path = "/Game/UserInterfaces/RoomEnterFailedWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			gameMode->CreateUIWidget( widget );
		}
		else if ( packet.Contains( SearchMacro::ROOM_ENTER ) )
		{
			FString path = "/Game/UserInterfaces/ChattingRoomWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			gameMode->ChangeMenuWidget( widget );
			gameMode->SetisChattingRoom( true );
		}

		else if ( packet.Contains( SearchMacro::ROOMINFO_FAILED ) )
		{
			///방 정보 실패
			FString path = "/Game/UserInterfaces/RoomInfoFailedWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			gameMode->CreateUIWidget( widget );
		}
		else if ( packet.Contains( SearchMacro::ROOMINFO_SUCCESS ) )
		{
			///방 정보 성공
			FString path = "/Game/UserInterfaces/RoomInfoWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			UUserWidget* UI = gameMode->CreateUIWidget( widget );

			if ( UI != nullptr )
				Cast<URoomInfo_Widget>( UI )->SetRoomInfo( packet );
			
		}
		else if ( packet.Contains( SearchMacro::USERINFO_FAILED ) )
		{
			///유저 정보 실패
			FString path = "/Game/UserInterfaces/UserInfoFailedWIdgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			gameMode->CreateUIWidget( widget );
		}
		else if ( packet.Contains( SearchMacro::USERINFO_SUCCESS ) )
		{
			///유저 정보 성공
			FString path = "/Game/UserInterfaces/UserInfoWidgetBP";
			TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
			UUserWidget* UI = gameMode->CreateUIWidget( widget );

			if ( UI != nullptr )
				Cast<UUserInfo_Widget>( UI )->SetUserInfo( packet );
		}
	}
	return false;
}
