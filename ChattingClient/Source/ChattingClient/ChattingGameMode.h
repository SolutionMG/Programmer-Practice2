// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ChattingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API AChattingGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "UMG Game" )
	TSubclassOf<UUserWidget> startingWidgetClass;



private:
	UPROPERTY( )
	bool m_isChattingRoom;
	/** The Widget class we will use as our menu when the game starts. */

		/** The widget instance that we are using as our menu. */
	UPROPERTY( )
	UUserWidget* CurrentWidget;
public:
	UFUNCTION( )
	void ChangeMenuWidget( TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION()
	void CreateUIWidget( TSubclassOf<UUserWidget> NewWidgetClass );

	UFUNCTION( BlueprintCallable )
	void SetisChattingRoom( const bool& isRoom );
	UFUNCTION( )
	const bool& GetisChattingRoom( );
	UFUNCTION( )
	UUserWidget* GetCurrentWidget( );

protected:
	/** Called when the game Starts. */
	virtual void BeginPlay( ) override;

	virtual void Tick( float DeletaSecond) override;


};
