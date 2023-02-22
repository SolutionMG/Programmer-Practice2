// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RoomCreate_Widget.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API URoomCreate_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomCreate_Button;

	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* RoomName_TextBox;

	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* RoomMax_TextBox;

	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct( ) override;

private:
	UFUNCTION( )
	void RequestCreateRoom();


};