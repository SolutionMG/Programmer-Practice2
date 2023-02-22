// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomEnterFailed_Widget.h"
#include "Runtime/UMG/Public/Components/Button.h"

void URoomEnterFailed_Widget::NativeConstruct()
{
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &URoomEnterFailed_Widget::QuitUI );
}

void URoomEnterFailed_Widget::QuitUI()
{
	this->RemoveFromParent();
}
