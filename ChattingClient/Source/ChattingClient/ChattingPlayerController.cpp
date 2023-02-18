// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingPlayerController.h"

void AChattingPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode( FInputModeGameAndUI() );
}
