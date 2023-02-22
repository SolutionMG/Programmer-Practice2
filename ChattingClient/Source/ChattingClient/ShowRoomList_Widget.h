// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowRoomList_Widget.generated.h"

/**
 * 
 */

class UButton;
class UScrollBox;

UCLASS()
class CHATTINGCLIENT_API UShowRoomList_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitUserList_Button;

	UPROPERTY( meta = ( BindWidget ) )
	UScrollBox* List_ScrollBox;

public:

	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

	//방 목록 추가
	UFUNCTION()
	bool AddRoomListWidget( const FString& Message );

private:
	UFUNCTION()
	void QuitUI();

};
