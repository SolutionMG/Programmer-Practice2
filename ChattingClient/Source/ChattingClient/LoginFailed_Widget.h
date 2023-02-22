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

	UPROPERTY( meta = ( BindWidget ) )
	UButton* LoginFailed_OffButton;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* LoginFailed_TextBox;

public:
	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

};
