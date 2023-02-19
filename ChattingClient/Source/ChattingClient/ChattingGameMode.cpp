// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingGameMode.h"


void AChattingGameMode::BeginPlay( )
{
	Super::BeginPlay( );
	ChangeMenuWidget( startingWidgetClass );
}
void AChattingGameMode::Tick( float DeletaSecond )
{

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
