// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomInfo_Widget.generated.h"

class UButton;
class UScrollBox;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API URoomInfo_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/// �� ���� �α׿� ����
	UPROPERTY( meta = ( BindWidget ) )
	UScrollBox* RoomInfo_Scrollbox;

	/// ���� ����� ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;
public:
	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct() override;

	/// �� ���� �α� ���� ��¿� ����
	UFUNCTION()
	void SetRoomInfo( const FString& info );
private:
	UFUNCTION()
	void QuitUI();
};
