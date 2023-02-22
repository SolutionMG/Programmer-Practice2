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
	//방 목록 추가
	UFUNCTION()
	bool AddRoomListWidget( const FString& Message );

	///해당 Widget 생성자 역할 함수
	UFUNCTION()
	virtual void NativeConstruct() override;
};
