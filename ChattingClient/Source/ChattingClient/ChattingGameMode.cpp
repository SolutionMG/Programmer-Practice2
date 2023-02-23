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
	AGameMode::Tick( DeletaSecond );

	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( !server )
	{
		UE_LOG( LogTemp, Warning, TEXT( "AChattingGameMode::Tick GetserverInstance Failed" ) );
		return;
	}
	server->ReceivePacket();

}
void AChattingGameMode::ChangeMenuWidget( TSubclassOf<UUserWidget> NewWidgetClass )
{
	if ( CurrentWidget )
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if ( !NewWidgetClass )
		return;
	CurrentWidget = CreateWidget<UUserWidget>( GetWorld( ), NewWidgetClass );

	if ( CurrentWidget != nullptr )
		CurrentWidget->AddToViewport( );
}

UUserWidget* AChattingGameMode::CreateUIWidget( TSubclassOf<UUserWidget> NewWidgetClass )
{
	if ( CurrentUI )
	{
		CurrentUI->RemoveFromViewport();
		CurrentUI = nullptr;
	}

	if ( !NewWidgetClass )
		return nullptr;
	
	CurrentUI = CreateWidget<UUserWidget>( GetWorld(), NewWidgetClass );

	if ( !CurrentUI )
		return nullptr;

	CurrentUI->AddToViewport();
	return CurrentUI;
}

void AChattingGameMode::SetisChattingRoom( const bool& isRoom )
{
	m_isChattingRoom = isRoom;
}
