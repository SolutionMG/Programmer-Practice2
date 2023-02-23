// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInfo_Widget.generated.h"

class UButton;
class UScrollBox;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UUserInfo_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/// 유저 정보 출력용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UScrollBox* UserInfo_Srcollbox;

	/// 위젯 종료용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;
public:
	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

	/// 유저 정보 출력하기
	UFUNCTION()
	void SetUserInfo( const FString& info );
private:
	UFUNCTION()
	void QuitUI();
};
