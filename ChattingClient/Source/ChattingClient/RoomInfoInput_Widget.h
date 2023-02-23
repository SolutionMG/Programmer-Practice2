// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomInfoInput_Widget.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API URoomInfoInput_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	/// 위젯 종료용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

	/// 방 번호 입력용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* RoomInfo_TextBox;

public:
	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void QuitUI();

	/// 방 정보 요청 보내기 함수
	UFUNCTION()
	void SendChatting( const FText& Text, ETextCommit::Type CommitMethod );
};
