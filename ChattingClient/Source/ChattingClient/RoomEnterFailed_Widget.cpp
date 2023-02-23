// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomEnterFailed_Widget.h"
#include "Runtime/UMG/Public/Components/Button.h"

void URoomEnterFailed_Widget::NativeConstruct()
{
	/// 버튼 함수에 바인딩
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &URoomEnterFailed_Widget::QuitUI );
}

void URoomEnterFailed_Widget::QuitUI()
{
	this->RemoveFromParent();
}
