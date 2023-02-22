// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SendSercretMessage.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API USendSercretMessage : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

	UPROPERTY( meta = ( BindWidget ) )

	UEditableTextBox* Name_EditableBox;

	UPROPERTY( meta = ( BindWidget ) )

	UEditableTextBox* Message_EditableBox;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* SendMessage_Button;


public:

	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void SendMessage();

	UFUNCTION()
	void QuitUI();
};
