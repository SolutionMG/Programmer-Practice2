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

	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct() override;

private:
	///Login Button Ŭ�� �� ȣ��� �Լ�
	UFUNCTION(  )
	void AccessRequest();
	/// ���� ���� �Լ�
	UFUNCTION(  )
	void QuitWidget();
};
