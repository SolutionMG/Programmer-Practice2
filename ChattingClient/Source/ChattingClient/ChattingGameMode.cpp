// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingGameMode.h"
#include "ServerManager.h"

 UUserWidget* AChattingGameMode::GetCurrentWidget( )
{
	return CurrentWidget;
}

void AChattingGameMode::BeginPlay( )
{
	Super::BeginPlay( );
	ChangeMenuWidget( startingWidgetClass );
	m_isChattingRoom = false;
}
const bool& AChattingGameMode::GetisChattingRoom( )
{
	// TODO: 여기에 return 문을 삽입합니다.
	return m_isChattingRoom;
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

void AChattingGameMode::CreateUIWidget( TSubclassOf<UUserWidget> NewWidgetClass )
{
	if ( NewWidgetClass != nullptr )
	{
		UUserWidget* NewWidget;
		NewWidget = CreateWidget<UUserWidget>( GetWorld(), NewWidgetClass );

		if ( NewWidget != nullptr )
		{
			NewWidget->AddToViewport();
		}
	}
}

void AChattingGameMode::SetisChattingRoom( const bool& isRoom )
{
	m_isChattingRoom = isRoom;
}
