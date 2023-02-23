// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomInfoFailed_Widget.h"
#include "Runtime/UMG/Public/Components/Button.h"

void URoomInfoFailed_Widget::NativeConstruct()
{
	/// 버튼에 함수 바인딩
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &URoomInfoFailed_Widget::QuitUI );
}

void URoomInfoFailed_Widget::QuitUI()
{
	this->RemoveFromParent();
}
