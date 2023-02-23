// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomCreateFailed_Widget.h"
#include "Runtime/UMG/Public/Components/Button.h"


void URoomCreateFailed_Widget::NativeConstruct()
{
	/// 버튼에 함수 바인딩
	if ( RoomCreateFailed_Button )
	{
		RoomCreateFailed_Button->OnClicked.AddDynamic( this, &URoomCreateFailed_Widget::QuitUI );
	}
}

void URoomCreateFailed_Widget::QuitUI()
{
	this->RemoveFromParent();
}
