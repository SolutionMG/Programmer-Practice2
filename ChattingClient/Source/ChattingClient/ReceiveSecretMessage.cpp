// Fill out your copyright notice in the Description page of Project Settings.


#include "ReceiveSecretMessage.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UReceiveSecretMessage::NativeConstruct()
{
	/// ��ư�� �Լ� ���ε�
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &UReceiveSecretMessage::QuitUI );
}

void UReceiveSecretMessage::SetMessage( const FString& message )
{
	/// �ؽ�Ʈ��Ͽ� �ӼӸ� ���� ���
	if ( !MessageTextBlock )
		return;

	TArray<FString> messageArray;
	const TCHAR* deletes[] = { TEXT( "\n\r" ), TEXT(">>")};
	message.ParseIntoArray( messageArray, deletes, 1 );

	FString parse;
	for ( int i = 0; i< messageArray.Num() - 2; ++i )
	{
		parse += messageArray[ i ];
	}

	MessageTextBlock->SetText( FText::FromString( parse ) );
}

void UReceiveSecretMessage::QuitUI()
{
	this->RemoveFromParent();
}
