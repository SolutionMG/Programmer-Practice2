 //Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_Widget.h"
#include "ServerManager.h"

#include "Kismet/KismetSystemLibrary.h"


void ULobby_Widget::NativeConstruct()
{
	if ( LobbyExit_Button )
		LobbyExit_Button->OnClicked.AddDynamic( this, &ULobby_Widget::QuitGame );

	if ( UserList_Button )
		UserList_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestUserList );

	if ( RoomList_Button )
		RoomList_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestRoomList );

	if ( UserInfo_Button )
		UserInfo_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestUserInfo );

	if( RoomInfo_Button )
		RoomInfo_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestRoomInfo );

	if ( RoomCreate_Button )
		RoomCreate_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestRoomCreate );

	if ( RoomEnter_Button )
		RoomEnter_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestRoomEnter );

}

void ULobby_Widget::QuitGame()
{
	UKismetSystemLibrary::QuitGame( this, 0, EQuitPreference::Quit, false );

}

void ULobby_Widget::RequestUserInfo()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == NULL )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestUserInfo server GetserverInstance Failed" ) );
		return;
	}

	//FString command = CommandMessage::PLAYERINFO;
	//server->SendPacket( command );
}

void ULobby_Widget::RequestUserList()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == NULL )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestUserList server GetserverInstance Failed" ) );
		return;
	}

	//FString command = CommandMessage::USERLIST ;
	//server->SendPacket( command );
}

void ULobby_Widget::RequestRoomList()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == NULL )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestRoomList server GetserverInstance Failed" ) );
		return;
	}

	//FString command = CommandMessage::ROOMLIST;
	//server->SendPacket( command );
}

void ULobby_Widget::RequestRoomInfo()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == NULL )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestRoomInfo server GetserverInstance Failed" ) );
		return;
	}

	//FString command = CommandMessage::ROOMINFO;
	//server->SendPacket( command );
}

void ULobby_Widget::RequestRoomCreate()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == NULL )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestRoomCreate server GetserverInstance Failed" ) );
		return;
	}

	//FString command = CommandMessage::ROOMCREATE;
	//server->SendPacket( command );
}

void ULobby_Widget::RequestRoomEnter()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == NULL )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestRoomEnter server GetserverInstance Failed" ) );
		return;
	}

	//FString command = CommandMessage::ROOMENTER;
	//server->SendPacket( command );
}
