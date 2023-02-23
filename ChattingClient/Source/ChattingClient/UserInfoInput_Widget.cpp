// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInfoInput_Widget.h"

#include "ServerManager.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

void UUserInfoInput_Widget::NativeConstruct()
{
	/// 버튼에 함수 바인딩
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &UUserInfoInput_Widget::QuitUI );
	if ( Name_Textblock )
		Name_Textblock->OnTextCommitted.AddDynamic( this, &UUserInfoInput_Widget::SendChatting );
}

void UUserInfoInput_Widget::QuitUI()
{
	this->RemoveFromParent();
}

void UUserInfoInput_Widget::SendChatting( const FText& Text, ETextCommit::Type CommitMethod )
{
	/// 유저 정보 요청 보내기
	if ( !Name_Textblock )
		return;

	switch ( CommitMethod )
	{
	case ETextCommit::Default:
		break;
	case ETextCommit::OnEnter:
	{
		if ( Text.IsEmpty() )
			return;

		FString parse = "PF ";
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

		Name_Textblock->SetText( FText::GetEmpty() );
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
