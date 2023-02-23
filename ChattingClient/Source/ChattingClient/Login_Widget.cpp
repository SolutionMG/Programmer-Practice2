// Fill out your copyright notice in the Description page of Project Settings.


#include "Login_Widget.h"
#include "ServerManager.h"
#include "LoginFailed_Widget.h"

#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

void ULogin_Widget::NativeConstruct()
{
	/// 버튼에 함수 바인딩
	if ( LoginRequest_Button )
	{
		LoginRequest_Button->OnClicked.AddDynamic( this, &ULogin_Widget::LoginRequest );
	}
}

void ULogin_Widget::LoginRequest()
{
	/// 로그인 요청 Send
	if ( !LoginName_TextBox )
	{
		UE_LOG( LogTemp, Warning, TEXT( "LoginRequest LoginName_TextBox is null" ) );
		return;
	}

	FString name = "LOGIN ";
	name += LoginName_TextBox->GetText().ToString();

	if (name.IsEmpty())
		return;

	UServerManager* server = Cast<UServerManager>(GetGameInstance());
	if (server == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoginRequest server->GetInstance Failed"));
		return;
	}

	if ( !server->SendPacket( name ) )
	{
		UE_LOG( LogTemp, Warning, TEXT( "LoginRequest server->SendPacket Failed" ) );
		return;
	}
}
