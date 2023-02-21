// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/Components/Button.h"

#include "Lobby_Widget.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ULobby_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY( meta = ( BindWidget ) )
	UButton* LobbyExit_Button;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* UserList_Button;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomList_Button;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* UserInfo_Button;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomInfo_Button;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomCreate_Button;
	
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

	/// 유저 정보 요청
	UFUNCTION()
	void RequestUserInfo();

	/// 방 정보 요청
	UFUNCTION()
	void RequestRoomInfo();

	/// 방 생성 요청
	UFUNCTION()
	void RequestRoomCreate();

	/// 방 입장 요청
	UFUNCTION()
	void RequestRoomEnter();
};
