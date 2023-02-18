// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChattingClientGameModeBase.h"
#include "ServerManager.h"

void AChattingClientGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget( startingWidgetClass );
}

void AChattingClientGameModeBase::ChangeMenuWidget( TSubclassOf<UUserWidget> NewWidgetClass )
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>( GetWorld(), NewWidgetClass );

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
