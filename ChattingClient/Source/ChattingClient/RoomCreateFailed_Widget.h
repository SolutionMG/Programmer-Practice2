// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomCreateFailed_Widget.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class CHATTINGCLIENT_API URoomCreateFailed_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomCreateFailed_Button;

public:
	///해당 Widget 생성자
	virtual void NativeConstruct() override;

private:
	void QuitUI();
};
