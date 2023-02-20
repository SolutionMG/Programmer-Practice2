// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Login_Widget.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ULogin_Widget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LoginPage_Title;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* LoginName_TextBox;

	UPROPERTY(meta = (BindWidget))
	UImage* LoginPage_Image;

	UPROPERTY(meta = (BindWidget))
	UButton* LoginRequest_Button;

public:
	///�ش� Widget ������
	void NativeConstruct() override;

	///LoginRequest Button Ŭ�� �� ȣ��� �Լ�
	UFUNCTION(BlueprintCallable)
	bool LoginRequest();//
};
