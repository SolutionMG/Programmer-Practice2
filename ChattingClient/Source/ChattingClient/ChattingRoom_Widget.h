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
	/// ä�� �α� ��¿� ����
	UPROPERTY( meta = ( BindWidget ) )
	UScrollBox* ChatLog;

	/// ä�� ���� ���ۿ� ����
	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* Message_TextBox;

	/// ä�ù� ����� ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* ChattingRoomQuit_Button;

	/// �ӼӸ� ���� Input ���� ������ ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* SecretMessage_Button;

	
public:
	/// �ش� Widget ������
	virtual void NativeConstruct( ) override;

	/// ä�� �α� �߰��� ����
	UFUNCTION( )
	bool AddChatLogWidget( const FString& Message );

private:
	/// ä�� �޽��� ������
	UFUNCTION( )
	void SendChatting( const FText& Text, ETextCommit::Type CommitMethod );

	/// ä�ù� ������
	UFUNCTION(BlueprintCallable)
	void QuitUI();

	/// �ӼӸ� ������
	UFUNCTION()
	void SendSecretMessage();

};
