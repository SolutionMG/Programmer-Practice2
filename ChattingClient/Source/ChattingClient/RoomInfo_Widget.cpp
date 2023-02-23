// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomInfo_Widget.h"

#include "Runtime/UMG/Public/Components/Textblock.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/Scrollbox.h"

void URoomInfo_Widget::NativeConstruct()
{
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &URoomInfo_Widget::QuitUI );
}

void URoomInfo_Widget::SetRoomInfo(const FString& info)
{
	if ( !RoomInfo_Scrollbox )
		return;

	TArray<FString> messageArray;
	const TCHAR* deletes[] = { TEXT( "\n\r") , TEXT(">>")};
	info.ParseIntoArray( messageArray, deletes, 1 );
	for ( int32 i = 0; i < messageArray.Num() - 1; ++i )
	{
		UTextBlock* NewTextBlock = NewObject<UTextBlock>();
		NewTextBlock->SetText( FText::FromString( messageArray[ i ] ) );
		NewTextBlock->SetColorAndOpacity( FLinearColor::Black );

		RoomInfo_Scrollbox->AddChild( NewTextBlock );
		RoomInfo_Scrollbox->ScrollToEnd();
	}
}

void URoomInfo_Widget::QuitUI()
{
	this->RemoveFromParent();
}
