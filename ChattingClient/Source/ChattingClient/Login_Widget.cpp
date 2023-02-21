// Fill out your copyright notice in the Description page of Project Settings.


#include "Login_Widget.h"
#include "ServerManager.h"
#include "LoginFailed_Widget.h"

void ULogin_Widget::NativeConstruct()
{
	if ( LoginRequest_Button != nullptr )
	{
		LoginRequest_Button->OnClicked.AddDynamic( this, &ULogin_Widget::LoginRequest );
	}
}

void ULogin_Widget::LoginRequest()
{
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
	if (server == NULL)
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
