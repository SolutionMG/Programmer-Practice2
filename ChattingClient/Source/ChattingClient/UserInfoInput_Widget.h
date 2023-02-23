// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInfoInput_Widget.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UUserInfoInput_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/// 위젯 종료용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

	/// 유저 정보 요청할 유저 이름 입출력 변수
	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* Name_Textblock;

public:

	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

private:
	
	UFUNCTION()
	void QuitUI();

	/// 유저 정보 요청 보내기
	UFUNCTION()
	void SendChatting( const FText& Text, ETextCommit::Type CommitMethod );
};
