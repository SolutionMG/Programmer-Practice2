// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Lobby_Widget.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ULobby_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	///해당 Widget 생성자
	virtual void NativeConstruct() override;
};
