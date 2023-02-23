// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ChattingRoom_Widget.generated.h"

class UButton;
class UScrollBox;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UChattingRoom_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/// 채팅 로그 출력용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UScrollBox* ChatLog;

	/// 채팅 문자 전송용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* Message_TextBox;

	/// 채팅방 퇴장용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* ChattingRoomQuit_Button;

	/// 귓속말 전송 Input 위젯 생성용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* SecretMessage_Button;

	
public:
	/// 해당 Widget 생성자
	virtual void NativeConstruct( ) override;

	/// 채팅 로그 추가용 변수
	UFUNCTION( )
	bool AddChatLogWidget( const FString& Message );

private:
	/// 채팅 메시지 보내기
	UFUNCTION( )
	void SendChatting( const FText& Text, ETextCommit::Type CommitMethod );

	/// 채팅방 나가기
	UFUNCTION(BlueprintCallable)
	void QuitUI();

	/// 귓속말 보내기
	UFUNCTION()
	void SendSecretMessage();

};
