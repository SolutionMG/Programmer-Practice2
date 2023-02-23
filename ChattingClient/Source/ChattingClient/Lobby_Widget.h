// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Lobby_Widget.generated.h"

class UButton;
class UScrollBox;
;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ULobby_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	/// 퇴장용 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* LobbyExit_Button;

	/// 유저 목록 요청 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* UserList_Button;

	/// 방 목록 요청 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomList_Button;

	/// 방 생성 Input 위젯 생성 요청 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomCreate_Button;
	
	/// 귓속말 Input 위젯 생성 요청 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* SecretMessage_Button;

	/// 유저 정보 요청 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* UserInfo_Button;

	/// 방 정보 요청 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomInfo_Button;

	/// 방입장 Input 위젯 생성 요청 변수
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomEnter_Button;

public:
	///해당 Widget 생성자
	virtual void NativeConstruct() override;

private:
	///게임 종료
	UFUNCTION()
	void QuitGame();

	/// 유저 목록 요청
	UFUNCTION()
	void RequestUserList();

	/// 방 목록 요청
	UFUNCTION()
	void RequestRoomList();

	/// 방 생성 요청
	UFUNCTION()
	void RequestRoomCreate();

	/// 귓속말 요청
	UFUNCTION( )
	void RequestSecretMessage( );

	/// 방 입장 요청
	UFUNCTION()
	void RequestRoomEnter();

	/// 방 정보 요청
	UFUNCTION()
	void RequestRoomInfo();

	/// 유저 정보 요청
	UFUNCTION()
	void RequestUserInfo();
};
