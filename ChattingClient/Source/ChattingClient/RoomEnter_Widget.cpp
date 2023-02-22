// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomEnter_Widget.h"
#include "ServerManager.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

void URoomEnter_Widget::NativeConstruct()
{
	if ( QuitButton )
		QuitButton->OnClicked.AddDynamic( this, &URoomEnter_Widget::QuitUI );
	if ( RoomEnter_Button )
		RoomEnter_Button->OnClicked.AddDynamic( this, &URoomEnter_Widget::RequestRoomEnter );
}

void URoomEnter_Widget::QuitUI()
{
	this->RemoveFromParent();
}

void URoomEnter_Widget::RequestRoomEnter()
{
	UServerManager* server = Cast<UServerManager>( GetGameInstance() );
	if ( server == nullptr )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestCreateRoom server GetserverInstance Failed" ) );
		return;
	}
	
	if ( !RoomNumber_Textbox )
		return;

	FString parse = "J ";
	parse += RoomNumber_Textbox->GetText().ToString();
	server->SendPacket( parse );
	this->RemoveFromParent();
}
