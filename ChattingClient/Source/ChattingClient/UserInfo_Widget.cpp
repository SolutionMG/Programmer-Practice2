// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInfo_Widget.h"

#include "Runtime/UMG/Public/Components/Textblock.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/Scrollbox.h"


void UUserInfo_Widget::NativeConstruct()
{
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &UUserInfo_Widget::QuitUI );
}

void UUserInfo_Widget::SetUserInfo( const FString& info )
{
	if ( !UserInfo_Srcollbox )
		return;

	UTextBlock* NewTextBlock = NewObject<UTextBlock>();
	NewTextBlock->SetText( FText::FromString( info ) );
	NewTextBlock->SetColorAndOpacity( FLinearColor::Black );
	UserInfo_Srcollbox->AddChild( NewTextBlock );
	UserInfo_Srcollbox->ScrollToEnd();
}

void UUserInfo_Widget::QuitUI()
{
	this->RemoveFromParent();
}