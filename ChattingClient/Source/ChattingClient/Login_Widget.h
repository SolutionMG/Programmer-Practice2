// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Login_Widget.generated.h"

/**
 * 
 */

class UTextBlock;
class UEditableTextBox;
class UImage;
class UButton;

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
private:
	UPROPERTY()
	TSubclassOf<UUserWidget> FailedWidget;
	
public:
	///�ش� Widget ������
	virtual void NativeConstruct() override;

	///LoginRequest Button Ŭ�� �� ȣ��� �Լ�
	UFUNCTION()
	void LoginRequest();

};
