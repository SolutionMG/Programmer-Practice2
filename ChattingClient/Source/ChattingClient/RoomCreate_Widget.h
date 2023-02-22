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

	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct( ) override;

private:
	UFUNCTION( )
	void RequestCreateRoom();


};
