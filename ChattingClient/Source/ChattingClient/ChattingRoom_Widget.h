// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ChattingRoom_Widget.generated.h"

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

public:
	///�ش� Widget ������
	virtual void NativeConstruct( ) override;

	//ä�÷α� �߰�
	UFUNCTION( )
	bool AddChatLogWidget( const FString& Message );

private:
	UFUNCTION( )
	void SendChatting( const FText& Text, ETextCommit::Type CommitMethod );


};
