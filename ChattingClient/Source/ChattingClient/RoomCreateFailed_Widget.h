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
	/// 规 积己 角菩 UI
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomCreateFailed_Button;

public:
	///秦寸 Widget 积己磊
	virtual void NativeConstruct() override;

private:
	void QuitUI();
};
