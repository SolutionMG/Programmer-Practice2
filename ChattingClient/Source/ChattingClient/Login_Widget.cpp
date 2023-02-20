// Fill out your copyright notice in the Description page of Project Settings.


#include "Login_Widget.h"
#include "ServerManager.h"

void ULogin_Widget::NativeConstruct()
{
}

bool ULogin_Widget::LoginRequest()
{
	if (!LoginName_TextBox)
		return false;

	FString name = "LOGIN ";
	name += LoginName_TextBox->GetText().ToString();

	if (name.IsEmpty())
		return false;

	UServerManager* server = Cast<UServerManager>(GetGameInstance());
	if (server == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoginRequest GetserverInstance Failed"));
		return false;
	}

	return server->SendPacket(name);
}
