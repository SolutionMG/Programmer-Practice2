 //Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_Widget.h"
#include "ServerManager.h"
#include "ChattingGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/UMG/Public/Components/Button.h"


void ULobby_Widget::NativeConstruct()
{
	/// 버튼에 각 함수 바인딩
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

	if( RoomEnter_Button )
		RoomEnter_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestRoomEnter );

	if ( RoomInfo_Button )
		RoomInfo_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestRoomInfo );

	if ( UserInfo_Button )
		UserInfo_Button->OnClicked.AddDynamic( this, &ULobby_Widget::RequestUserInfo );
}

void ULobby_Widget::QuitGame()
{
	/// 게임 종료
	UKismetSystemLibrary::QuitGame( this, 0, EQuitPreference::Quit, false );

}

void ULobby_Widget::RequestUserList()
{
	/// 유저 정보 요청 Send
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
	/// 방 목록 요청 Send
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
	/// 방 만들기 UI 생성
	FString path = "/Game/UserInterfaces/RoomCreateWidgetBP";
	TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass( ) );
	Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld( ) ) )->ChangeUIWidget( widget );
}

void ULobby_Widget::RequestSecretMessage( )
{
	/// 귓속말 UI 생성
	FString path = "/Game/UserInterfaces/SendSecretMessageWidgetBP";
	TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
	Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) )->ChangeUIWidget( widget );
}

void ULobby_Widget::RequestRoomEnter()
{
	///방 입장 번호 입력 UI
	FString path = "/Game/UserInterfaces/RoomEnterWidgetBP";
	TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
	Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) )->ChangeUIWidget( widget );
}

void ULobby_Widget::RequestRoomInfo()
{
	///방 정보 UI
	FString path = "/Game/UserInterfaces/RoomInfoInputWidgetBP";
	TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
	Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) )->ChangeUIWidget( widget );
}

void ULobby_Widget::RequestUserInfo()
{
	///유저 정보 UI
	FString path = "/Game/UserInterfaces/UserInfoInputWidgetBP";
	TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
	Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) )->ChangeUIWidget( widget );
}


