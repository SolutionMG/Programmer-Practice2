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
	/// 방 생성 요청용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomCreate_Button;

	/// 방 이름용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* RoomName_TextBox;

	/// 방 인원용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* RoomMax_TextBox;

	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct( ) override;

private:
	/// 방생성 요청 함수
	UFUNCTION( )
	void RequestCreateRoom();

};
