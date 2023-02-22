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

	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct() override;

	//�� ��� �߰�
	UFUNCTION()
	bool AddRoomListWidget( const FString& Message );

private:
	UFUNCTION()
	void QuitUI();

};