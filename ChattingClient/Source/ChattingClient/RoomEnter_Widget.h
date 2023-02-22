// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomEnter_Widget.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API URoomEnter_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomEnter_Button;

	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* RoomNumber_Textbox;

public:
	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void QuitUI();

	UFUNCTION()
	void RequestRoomEnter();
};
