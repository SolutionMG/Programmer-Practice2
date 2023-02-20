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

	///해당 Widget 생성자
	void NativeConstruct() override;

	///Login Button 클릭 시 호출될 함수
	UFUNCTION(BlueprintCallable)
	bool AccessRequest(TSubclassOf<UUserWidget> NewWidgetClass);
};
