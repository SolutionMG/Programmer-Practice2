// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomInfoInput_Widget.h"

#include "ServerManager.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

void URoomInfoInput_Widget::NativeConstruct()
{
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &URoomInfoInput_Widget::QuitUI );
	if ( RoomInfo_TextBox )
		RoomInfo_TextBox->OnTextCommitted.AddDynamic( this, &URoomInfoInput_Widget::SendChatting );
}


void URoomInfoInput_Widget::QuitUI()
{
	this->RemoveFromParent();
}

void URoomInfoInput_Widget::SendChatting( const FText& Text, ETextCommit::Type CommitMethod )
{
	if ( !RoomInfo_TextBox )
		return;
	switch ( CommitMethod )
	{
	case ETextCommit::Default:
		break;
	case ETextCommit::OnEnter:
	{
		if ( Text.IsEmpty() )
			return;

		FString parse = "ST ";
		parse += Text.ToString();

		UServerManager* server = Cast<UServerManager>( GetGameInstance() );
		if ( server == nullptr )
		{
			UE_LOG( LogTemp, Warning, TEXT( "LoginRequest server->GetInstance Failed" ) );
			return;
		}

		if ( !server->SendPacket( parse ) )
		{
			UE_LOG( LogTemp, Warning, TEXT( "LoginRequest server->SendPacket Failed" ) );
			return;
		}


		RoomInfo_TextBox->SetText( FText::GetEmpty() );
		this->RemoveFromParent();
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
