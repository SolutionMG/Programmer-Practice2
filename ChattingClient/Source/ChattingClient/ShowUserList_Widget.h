// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowUserList_Widget.generated.h"

class UButton;
class UScrollBox;

/**
 * 
 */


UCLASS()
class CHATTINGCLIENT_API UShowUserList_Widget : public UUserWidget
{
	GENERATED_BODY()
public:
	/// 위젯 종료용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitUserList_Button;

	/// 유저 목록 출력용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UScrollBox* List_ScrollBox;

public:

	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

	//유저 목록 추가
	UFUNCTION()
	bool AddUserListWidget( const FString& Message );

private:
	UFUNCTION()
	void QuitUI();
};
