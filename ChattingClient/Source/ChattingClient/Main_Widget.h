// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/Components/Button.h"

#include "Main_Widget.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UMain_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LoginButton;
public:

	///�ش� Widget ������
	void NativeConstruct() override;

	///Login Button Ŭ�� �� ȣ��� �Լ�
	UFUNCTION(BlueprintCallable)
	bool AccessRequest(TSubclassOf<UUserWidget> NewWidgetClass);
};
