// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowRoomList_Widget.h"
#include "Runtime/UMG/Public/Components/Scrollbox.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"


void UShowRoomList_Widget::NativeConstruct()
{
	if ( QuitUserList_Button != nullptr )
	{
		QuitUserList_Button->OnClicked.AddDynamic( this, &UShowRoomList_Widget::QuitUI );
	}
}

bool UShowRoomList_Widget::AddRoomListWidget( const FString& Message )
{
	if ( !List_ScrollBox )
		return false;

	TArray<FString> messageArray;
	const TCHAR* deletes[] = { TEXT( "\n\r" ) };
	Message.ParseIntoArray( messageArray, deletes, 1 );
	for ( int32 i = 0; i < messageArray.Num() - 2; ++i )
	{
		UTextBlock* NewTextBlock = NewObject<UTextBlock>();
		NewTextBlock->SetText( FText::FromString( messageArray[ i ] ) );
		NewTextBlock->SetColorAndOpacity( FLinearColor::Black );

		List_ScrollBox->AddChild( NewTextBlock );
		List_ScrollBox->ScrollToEnd();
	}

	return true;
}

void UShowRoomList_Widget::QuitUI()
{
	this->RemoveFromParent();
}

