// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Lobby_Widget.generated.h"

class UButton;
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
	UButton* RoomCreate_Button;
	
	UPROPERTY( meta = ( BindWidget ) )
	UButton* SecretMessage_Button;

public:
	///秦寸 Widget 积己磊
	virtual void NativeConstruct() override;

private:
	///霸烙 辆丰
	UFUNCTION()
	void QuitGame();

	/// 蜡历 格废 夸没
	UFUNCTION()
	void RequestUserList();

	/// 规 格废 夸没
	UFUNCTION()
	void RequestRoomList();

	/// 规 积己 夸没
	UFUNCTION()
	void RequestRoomCreate();

	/// 庇加富 夸没
	UFUNCTION( )
	void RequestSecretMessage( );

};
