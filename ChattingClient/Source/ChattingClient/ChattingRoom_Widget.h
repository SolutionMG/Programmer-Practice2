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
	UPROPERTY( meta = ( BindWidget ) )
	UScrollBox* ChatLog;

	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* Message_TextBox;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* ChattingRoomQuit_Button;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* SecretMessage_Button;

	
public:
	///�ش� Widget ������
	virtual void NativeConstruct( ) override;

	//ä�÷α� �߰�
	UFUNCTION( )
	bool AddChatLogWidget( const FString& Message );

private:
	UFUNCTION( )
	void SendChatting( const FText& Text, ETextCommit::Type CommitMethod );

	UFUNCTION(BlueprintCallable)
	void QuitUI();

	UFUNCTION()
	void SendSecretMessage();

};
