// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInfo_Widget.generated.h"

class UButton;
class UScrollBox;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UUserInfo_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/// ���� ���� ��¿� ����
	UPROPERTY( meta = ( BindWidget ) )
	UScrollBox* UserInfo_Srcollbox;

	/// ���� ����� ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;
public:
	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct() override;

	/// ���� ���� ����ϱ�
	UFUNCTION()
	void SetUserInfo( const FString& info );
private:
	UFUNCTION()
	void QuitUI();
};
