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
	if ( Message_TextBox )
		Message_TextBox->OnTextCommitted.AddDynamic( this, &UChattingRoom_Widget::SendChatting );
	//if ( ChattingRoomQuit_Button )
	//	ChattingRoomQuit_Button->OnClicked.AddDynamic( this, &UChattingRoom_Widget::QuitUI );
}

void UChattingRoom_Widget::SendChatting( const FText& Text, ETextCommit::Type CommitMethod )
{
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

		TArray<FString> parseArray;

		FString parse = Text.ToString();
		const TCHAR* deletes[] = { TEXT( "\n\r" ), TEXT("\n")};
		parse.ParseIntoArray( parseArray, deletes, 1 );

		FString parse2;
		for ( const auto& m : parseArray )
		{
			if ( m != "\n\r" && m != ">>" && m!="\n" )
				parse2 += m;
		}

		UTextBlock* NewTextBlock = NewObject<UTextBlock>( );
		NewTextBlock->SetText( FText::FromString( parse2) );
		NewTextBlock->SetColorAndOpacity( FLinearColor::Black );
		ChatLog->AddChild( NewTextBlock );
		ChatLog->ScrollToEnd( );
		Message_TextBox->SetText( FText() );
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

	AChattingGameMode* gameMode = Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	if ( !gameMode )
		return;

	this->RemoveFromParent();
}

bool UChattingRoom_Widget::AddChatLogWidget( const FString& Message )
{
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
