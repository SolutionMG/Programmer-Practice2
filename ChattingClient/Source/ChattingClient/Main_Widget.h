// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "Main_Widget.generated.h"


class UButton;
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
private:
	UPROPERTY()
	TSubclassOf<UUserWidget> NextWidgetClass;
public:
	UMain_Widget( const FObjectInitializer& ObjectInitializer );

	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

private:
	///Login Button 클릭 시 호출될 함수
	UFUNCTION(  )
	void AccessRequest();
	/// 게임 종료 함수
	UFUNCTION(  )
	void QuitWidget();
};
