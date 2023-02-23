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

	/// 로그인 페이지 타이틀 변수
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LoginPage_Title;

	/// 로그인 요청할 이름 입력용 변수
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* LoginName_TextBox;

	/// 로그인 페이지 배경 이미지 변수
	UPROPERTY(meta = (BindWidget))
	UImage* LoginPage_Image;

	/// 로그인 요청 버튼 변수
	UPROPERTY(meta = (BindWidget))
	UButton* LoginRequest_Button;
private:
	/// 로그인 실패 위젯 subclass
	UPROPERTY()
	TSubclassOf<UUserWidget> FailedWidget;
	
public:
	///해당 Widget 생성자
	virtual void NativeConstruct() override;

	///LoginRequest Button 클릭 시 호출될 함수
	UFUNCTION()
	void LoginRequest();

};
