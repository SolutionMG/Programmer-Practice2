// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowUserList_Widget.h"
#include "Runtime/UMG/Public/Components/Scrollbox.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"


void UShowUserList_Widget::NativeConstruct()
{
	/// 버튼에 함수 바인딩
	if ( QuitUserList_Button != nullptr )
	{
		QuitUserList_Button->OnClicked.AddDynamic( this, &UShowUserList_Widget::QuitUI );
	}
}

void UShowUserList_Widget::QuitUI()
{
	this->RemoveFromParent();
}

bool UShowUserList_Widget::AddUserListWidget( const FString& Message )
{
	/// 유저 목록 출력
	if ( !List_ScrollBox )
		return false;

	TArray<FString> messageArray;
	const TCHAR* deletes[] = { TEXT( "\n\r" )};
	Message.ParseIntoArray( messageArray, deletes, 1 );
	for (int32 i = 0; i< messageArray.Num() - 2; ++i)
	{
		UTextBlock* NewTextBlock = NewObject<UTextBlock>();
		NewTextBlock->SetText( FText::FromString( messageArray[i]));
		NewTextBlock->SetColorAndOpacity( FLinearColor::Black );

		List_ScrollBox->AddChild( NewTextBlock );
		List_ScrollBox->ScrollToEnd();
	}

	return true;
}

