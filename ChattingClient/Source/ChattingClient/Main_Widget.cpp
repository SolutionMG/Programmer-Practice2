// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Widget.h"
#include "ServerManager.h"
#include "ChattingGameMode.h"
#include "Login_Widget.h"
#include "Runtime/UMG/Public/Components/Button.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UMain_Widget::UMain_Widget( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	/// 다음 위젯 불러오기
	static ConstructorHelpers::FClassFinder<UUserWidget> NextUI( TEXT( "/Game/UserInterfaces/LoginWidgetBP" ) );

	if ( NextUI.Succeeded() )
	{
		NextWidgetClass = NextUI.Class;

	}
}

void UMain_Widget::NativeConstruct()
{
	/// 각 버튼 함수 바인딩
	if ( LoginButton )
	{
		LoginButton->OnClicked.AddDynamic( this, &UMain_Widget::AccessRequest );
	}

	if ( QuitButton )
	{
		QuitButton->OnClicked.AddDynamic( this, &UMain_Widget::QuitWidget );
	}
}


void UMain_Widget::AccessRequest()
{
	/// 위젯 로그인 위젯으로 변경
	UServerManager* server = Cast<UServerManager>(GetGameInstance());
	if (server == nullptr)
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

void UMain_Widget::QuitWidget()
{
	UKismetSystemLibrary::QuitGame( this, 0, EQuitPreference::Quit, false );
}

