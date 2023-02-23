// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInfoFailed_Widget.h"
#include "Runtime/UMG/Public/Components/Button.h"

void UUserInfoFailed_Widget::NativeConstruct()
{
	///버튼에 함수 바인딩
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &UUserInfoFailed_Widget::QuitUI );
}

void UUserInfoFailed_Widget::QuitUI()
{
	this->RemoveFromParent();
}
