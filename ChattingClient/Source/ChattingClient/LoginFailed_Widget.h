// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginFailed_Widget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ULoginFailed_Widget : public UUserWidget
{
	GENERATED_BODY()
public:
	/// UI ����� ��ư
	UPROPERTY( meta = ( BindWidget ) )
	UButton* LoginFailed_OffButton;

	/// �α��� ���� �ؽ�Ʈ ���� ��ư
	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* LoginFailed_TextBox;

public:
	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct() override;

};
