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
	/// ����� ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* LobbyExit_Button;

	/// ���� ��� ��û ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* UserList_Button;

	/// �� ��� ��û ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomList_Button;

	/// �� ���� Input ���� ���� ��û ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomCreate_Button;
	
	/// �ӼӸ� Input ���� ���� ��û ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* SecretMessage_Button;

	/// ���� ���� ��û ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* UserInfo_Button;

	/// �� ���� ��û ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomInfo_Button;

	/// ������ Input ���� ���� ��û ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* RoomEnter_Button;

public:
	///�ش� Widget ������
	virtual void NativeConstruct() override;

private:
	///���� ����
	UFUNCTION()
	void QuitGame();

	/// ���� ��� ��û
	UFUNCTION()
	void RequestUserList();

	/// �� ��� ��û
	UFUNCTION()
	void RequestRoomList();

	/// �� ���� ��û
	UFUNCTION()
	void RequestRoomCreate();

	/// �ӼӸ� ��û
	UFUNCTION( )
	void RequestSecretMessage( );

	/// �� ���� ��û
	UFUNCTION()
	void RequestRoomEnter();

	/// �� ���� ��û
	UFUNCTION()
	void RequestRoomInfo();

	/// ���� ���� ��û
	UFUNCTION()
	void RequestUserInfo();
};
