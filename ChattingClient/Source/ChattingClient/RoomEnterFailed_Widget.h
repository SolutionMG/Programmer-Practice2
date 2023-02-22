// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomEnterFailed_Widget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API URoomEnterFailed_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

public:
	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void QuitUI();
};
