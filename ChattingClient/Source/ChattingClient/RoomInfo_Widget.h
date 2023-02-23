// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomInfo_Widget.generated.h"

class UButton;
class UScrollBox;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API URoomInfo_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/// 방 정보 로그용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UScrollBox* RoomInfo_Scrollbox;

	/// 위젯 종료용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;
public:
	///해당 Widget 생성자 역할 함수
	virtual void NativeConstruct() override;

	/// 방 정보 로그 문자 출력용 변수
	UFUNCTION()
	void SetRoomInfo( const FString& info );
private:
	UFUNCTION()
	void QuitUI();
};
