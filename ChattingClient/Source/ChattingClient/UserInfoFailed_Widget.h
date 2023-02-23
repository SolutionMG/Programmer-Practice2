// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInfoFailed_Widget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UUserInfoFailed_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/// 위젯 종료용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

public:
	/// 해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void QuitUI();
};
