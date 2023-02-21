// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/Scrollbox.h"

#include "ChattingRoom_Widget.generated.h"

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
	///해당 Widget 생성자
	virtual void NativeConstruct( ) override;

	//채팅로그 추가
	UFUNCTION( )
	bool AddChatLogWidget( const FString& Message );
public:

private:
	UFUNCTION( )
	void SendChatting( const FText& Text, ETextCommit::Type CommitMethod );


};
