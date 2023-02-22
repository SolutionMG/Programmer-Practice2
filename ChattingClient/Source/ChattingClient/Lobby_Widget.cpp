 //Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_Widget.h"
#include "ServerManager.h"
#include "ChattingGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/UMG/Public/Components/Button.h"


void ULobby_Widget::NativeConstruct()
{
	if ( LobbyExit_Button )
		LobbyExit_Button->OnClicked.AddDynamic( this, &ULobby_Widget::QuitGame );

	if ( UserList_Button )
		UserList_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestUserList );

	if ( RoomList_Button )
		RoomList_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestRoomList );

	if ( RoomCreate_Button )
		RoomCreate_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestRoomCreate );

	if ( SecretMessage_Button )
		SecretMessage_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestSecretMessage );

}

void ULobby_Widget::QuitGame()
{
	UKismetSystemLibrary::QuitGame( this, 0, EQuitPreference::Quit, false );

}

void ULobby_Widget::RequestUserList()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == nullptr )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestUserList server GetserverInstance Failed" ) );
		return;
	}

	server->SendPacket( "US" );
}

void ULobby_Widget::RequestRoomList()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == nullptr )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestRoomList server GetserverInstance Failed" ) );
		return;
	}

	server->SendPacket( "LT" );
}


void ULobby_Widget::RequestRoomCreate()
{
	//방 만들기 UI 생성
	FString path = "/Game/UserInterfaces/RoomCreateWidgetBP";
	TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass( ) );
	Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld( ) ) )->CreateUIWidget( widget );
}

void ULobby_Widget::RequestSecretMessage( )
{
}


