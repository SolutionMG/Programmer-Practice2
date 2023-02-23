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
	return m_isChattingRoom;
}
void AChattingGameMode::Tick( float DeletaSecond )
{
	AGameMode::Tick( DeletaSecond );

	/// 논블로킹 서버 Receive함수 호출
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
	/// 메인 위젯 삭제 후 새로 지정
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

UUserWidget* AChattingGameMode::ChangeUIWidget( TSubclassOf<UUserWidget> NewWidgetClass )
{
	/// 메인 팝업 삭제 후 새로 지정
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

UUserWidget* AChattingGameMode::CreateUIWidget( TSubclassOf<UUserWidget> NewWidgetClass )
{
	/// 새 팝업 생성
	if ( !NewWidgetClass )
		return nullptr;

	UUserWidget* NewUI = CreateWidget<UUserWidget>( GetWorld(), NewWidgetClass );
	if ( !NewUI )
		return nullptr;

	NewUI->AddToViewport();

	return NewUI;
}

void AChattingGameMode::SetisChattingRoom( const bool& isRoom )
{
	m_isChattingRoom = isRoom;
}
