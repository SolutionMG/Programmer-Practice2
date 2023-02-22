// Fill out your copyright notice in the Description page of Project Settings.


#include "SendSercretMessage.h"

#include "ServerManager.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/Scrollbox.h"

void USendSercretMessage::NativeConstruct()
{
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &USendSercretMessage::QuitUI );

	if ( SendMessage_Button )
		SendMessage_Button->OnClicked.AddDynamic( this, &USendSercretMessage::SendMessage );
}

void USendSercretMessage::SendMessage()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == nullptr )
	{
		UE_LOG( LogTemp, Warning, TEXT( "SendMessage server->GetInstance Failed" ) );
		return;
	}

	if ( !Name_EditableBox )
		return;

	if ( !Message_EditableBox )
		return;

	FString parse = "TO ";
	parse += Name_EditableBox->GetText().ToString();
	parse += " ";
	parse += Message_EditableBox->GetText().ToString();

	if ( !server->SendPacket( parse ) )
	{
		UE_LOG( LogTemp, Warning, TEXT( "SendMessage server->SendPacket Failed" ) );
		return;
	}

	this->RemoveFromParent();
}

void USendSercretMessage::QuitUI()
{
	this->RemoveFromParent();
}
