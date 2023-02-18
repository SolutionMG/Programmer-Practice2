// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChattingClientGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API AChattingClientGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category = "UMG Game" )
	void ChangeMenuWidget( TSubclassOf<UUserWidget> NewWidgetClass );

protected:
	/** Called when the game Starts. */
	virtual void BeginPlay() override;

	/** The Widget class we will use as our menu when the game starts. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "UMG Game" )
	TSubclassOf<UUserWidget> startingWidgetClass;

	/** The widget instance that we are using as our menu. */
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
