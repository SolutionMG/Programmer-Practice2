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
	/// 위젯 종료용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

	/// 귓속말 전송할 대상 이름용 변수
	UPROPERTY( meta = ( BindWidget ) )

	UEditableTextBox* Name_EditableBox;

	/// 귓속말 메시지용 변수
	UPROPERTY( meta = ( BindWidget ) )

	UEditableTextBox* Message_EditableBox;

	/// 귓속말 보내기용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* SendMessage_Button;


public:

	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

private:
	/// 귓속말 보내기 함수
	UFUNCTION()
	void SendMessage();

	UFUNCTION()
	void QuitUI();
};
