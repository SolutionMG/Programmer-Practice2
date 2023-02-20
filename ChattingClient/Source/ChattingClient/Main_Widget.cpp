// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Widget.h"
#include "ServerManager.h"
#include "ChattingGameMode.h"
#include "Kismet/GameplayStatics.h"

bool UMain_Widget::AccessRequest(TSubclassOf<UUserWidget> NewWidgetClass)
{
	UServerManager* server = Cast<UServerManager>(GetGameInstance());
	if (server == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoginRequest GetserverInstance Failed"));
		return false;
	}

	bool returnValue = server->ConnectToServer();
	if (!returnValue)
	{
		return false;
	}

	Cast<AChattingGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->ChangeMenuWidget(NewWidgetClass);

	return true;

}

void UMain_Widget::NativeConstruct()
{
}
