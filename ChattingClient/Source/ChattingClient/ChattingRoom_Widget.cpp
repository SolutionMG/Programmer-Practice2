// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingRoom_Widget.h"
#include "ServerManager.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UChattingRoom_Widget::NativeConstruct( )
{
	if ( Message_TextBox )
		Message_TextBox->OnTextCommitted.AddDynamic( this, &UChattingRoom_Widget::SendChatting );
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
		if ( server == NULL )
		{
			UE_LOG( LogTemp, Warning, TEXT( "LoginRequest server->GetInstance Failed" ) );
			return;
		}

		if ( !server->SendPacket( Message_TextBox->GetText( ).ToString( ) ) )
		{
			UE_LOG( LogTemp, Warning, TEXT( "LoginRequest server->SendPacket Failed" ) );
			return;
		}
		UTextBlock* NewTextBlock = NewObject<UTextBlock>( );
		NewTextBlock->SetText( Text);
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
