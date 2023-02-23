// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReceiveSecretMessage.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UReceiveSecretMessage : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/// 종료용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

	/// 귓속말 내용 텍스트 변수 
	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* MessageTextBlock;

public:
	///해당 Widget 생성자
	virtual void NativeConstruct() override;

	/// 귓속말 메시지 UI에출력
	UFUNCTION()
	void SetMessage(const FString& message);

private:
	UFUNCTION()
	void QuitUI();
};
