// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingRoom_Widget.h"
#include "ServerManager.h"
#include "ChattingGameMode.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/Scrollbox.h"

void UChattingRoom_Widget::NativeConstruct( )
{
	/// 버튼 클릭, 엔터 입력에 따른 함수 바인딩
	if ( Message_TextBox )
		Message_TextBox->OnTextCommitted.AddDynamic( this, &UChattingRoom_Widget::SendChatting );

	if ( SecretMessage_Button )
		SecretMessage_Button->OnClicked.AddDynamic( this, &UChattingRoom_Widget::SendSecretMessage );

	//if ( ChattingRoomQuit_Button )
	//	ChattingRoomQuit_Button->OnClicked.AddDynamic( this, &UChattingRoom_Widget::QuitUI );
}

void UChattingRoom_Widget::SendChatting( const FText& Text, ETextCommit::Type CommitMethod )
{
	/// Enter 클릭 시 Text 보내기 & 채팅 로그 추가하기
	switch ( CommitMethod )
	{
	case ETextCommit::Default:
	break;
	case ETextCommit::OnEnter:
	{
		if ( Text.IsEmpty( ) )
			return;

		UServerManager* server = Cast<UServerManager>( GetGameInstance( ) );
		if ( server == nullptr )
		{
			UE_LOG( LogTemp, Warning, TEXT( "LoginRequest server->GetInstance Failed" ) );
			return;
		}

		if ( !server->SendPacket( Message_TextBox->GetText( ).ToString( ) ) )
		{
			UE_LOG( LogTemp, Warning, TEXT( "LoginRequest server->SendPacket Failed" ) );
			return;
		}

		AddChatLogWidget( Text.ToString() );
		Message_TextBox->SetText( FText::GetEmpty() );
	}
	break;
	case ETextCommit::OnUserMovedFocus:
	break;
	case ETextCommit::OnCleared:
	break;
	default:
	break;
	}
}

void UChattingRoom_Widget::QuitUI()
{
	/// 채팅방 나가기 
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( !server )
	{
		UE_LOG( LogTemp, Warning, TEXT( "LoginRequest server->GetInstance Failed" ) );
		return;
	}

	if ( !server->SendPacket( "/X") )
	{
		UE_LOG( LogTemp, Warning, TEXT( "LoginRequest server->SendPacket Failed" ) );
		return;
	}

	this->RemoveFromParent();
}

void UChattingRoom_Widget::SendSecretMessage()
{
	///귓속말 UI 생성
	FString path = "/Game/UserInterfaces/SendSecretMessageWidgetBP";
	TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass( path, UUserWidget::StaticClass() );
	Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) )->ChangeUIWidget( widget );
}

bool UChattingRoom_Widget::AddChatLogWidget( const FString& Message )
{
	/// 채팅 로그 메시지 추가하기
	if ( !ChatLog )
		return false; 

	TArray<FString> messageArray;
	const TCHAR* deletes[ ] = { TEXT( "\n\r" ), TEXT(">>" ) };
	Message.ParseIntoArray( messageArray, deletes, 1 );

	FString parse;
	for ( const auto& m : messageArray )
	{
		if ( m != "\n\r" && m!= ">>" )
			parse += m;
	}

	UTextBlock* NewTextBlock = NewObject<UTextBlock>( );
	NewTextBlock->SetText( FText::FromString( parse ) );
	NewTextBlock->SetColorAndOpacity( FLinearColor::Black );

	ChatLog->AddChild( NewTextBlock );
	ChatLog->ScrollToEnd( );

	return true;
}
