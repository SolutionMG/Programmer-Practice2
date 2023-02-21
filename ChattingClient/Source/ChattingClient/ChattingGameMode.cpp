// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingGameMode.h"
#include "ServerManager.h"

void AChattingGameMode::BeginPlay( )
{
	Super::BeginPlay( );
	ChangeMenuWidget( startingWidgetClass );
}
void AChattingGameMode::Tick( float DeletaSecond )
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == NULL )
	{
		UE_LOG( LogTemp, Warning, TEXT( "AChattingGameMode::Tick GetserverInstance Failed" ) );
		return;
	}
	server->ReceivePacket();
	

}
void AChattingGameMode::ChangeMenuWidget( TSubclassOf<UUserWidget> NewWidgetClass )
{
	if ( CurrentWidget != nullptr )
	{
		CurrentWidget->RemoveFromViewport( );
		CurrentWidget = nullptr;
	}

	if ( NewWidgetClass != nullptr )
	{
		CurrentWidget = CreateWidget<UUserWidget>( GetWorld( ), NewWidgetClass );

		if ( CurrentWidget != nullptr )
		{
			CurrentWidget->AddToViewport( );
		}
	}
}

void AChattingGameMode::OffMenuWidget()
{
	if ( CurrentWidget != nullptr )
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
}
