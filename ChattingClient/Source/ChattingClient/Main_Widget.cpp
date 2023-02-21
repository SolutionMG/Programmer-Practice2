// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Widget.h"
#include "ServerManager.h"
#include "ChattingGameMode.h"
#include "Login_Widget.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UMain_Widget::UMain_Widget( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	static ConstructorHelpers::FClassFinder<UUserWidget> NextUI( TEXT( "/Game/UserInterfaces/LoginWidgetBP" ) );

	if ( NextUI.Succeeded() )
	{
		NextWidgetClass = NextUI.Class;

	}
}

void UMain_Widget::NativeConstruct()
{

	if ( LoginButton != nullptr)
	{
		LoginButton->OnClicked.AddDynamic( this, &UMain_Widget::AccessRequest );
	}

	if ( QuitButton != nullptr)
	{
		QuitButton->OnClicked.AddDynamic( this, &UMain_Widget::QuitGameReqeust );
	}
}


void UMain_Widget::AccessRequest()
{
	UServerManager* server = Cast<UServerManager>(GetGameInstance());
	if (server == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoginRequest GetserverInstance Failed"));
		return;
	}

	bool returnValue = server->ConnectToServer();
	if (!returnValue)
	{
		UE_LOG( LogTemp, Warning, TEXT( "AccessRequest ConnectToServer Failed" ) );
		return;
	}

	Cast<AChattingGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) )->ChangeMenuWidget( NextWidgetClass );
}

void UMain_Widget::QuitGameReqeust()
{
	UKismetSystemLibrary::QuitGame( this, 0, EQuitPreference::Quit, false );
}

