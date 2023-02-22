// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReceiveSecretMessage.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UReceiveSecretMessage : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* MessageTextBlock;

public:
	///해당 Widget 생성자
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetMessage(const FString& message);

private:
	UFUNCTION()
	void QuitUI();
};
