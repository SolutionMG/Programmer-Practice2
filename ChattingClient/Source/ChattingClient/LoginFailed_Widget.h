// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginFailed_Widget.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ULoginFailed_Widget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY( meta = ( BindWidget ) )
	UButton* LoginFailed_OffButton;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* LoginFailed_TextBox;

public:
	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct() override;

};
