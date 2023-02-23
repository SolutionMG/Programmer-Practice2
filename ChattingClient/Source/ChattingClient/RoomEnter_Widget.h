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
	/// 위젯 종료용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

	/// 방 입장 요청용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomEnter_Button;

	/// 방 번호 입력 변수
	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* RoomNumber_Textbox;

public:
	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void QuitUI();

	/// 방 입장 요청 함수
	UFUNCTION()
	void RequestRoomEnter();
};
