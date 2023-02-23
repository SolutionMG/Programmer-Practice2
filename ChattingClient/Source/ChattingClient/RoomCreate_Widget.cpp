// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomCreate_Widget.h"
#include "ServerManager.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

void URoomCreate_Widget::NativeConstruct( )
{
	/// ��ư�� �Լ� ���ε�
	if ( RoomCreate_Button != nullptr )
	{
		RoomCreate_Button->OnClicked.AddDynamic( this, &URoomCreate_Widget::RequestCreateRoom );
	}
}

void URoomCreate_Widget::RequestCreateRoom( )
{
	/// �� ���� ��û Send �� UI ����
	UServerManager* server = Cast<UServerManager>( GetGameInstance( ) );
	if ( server == nullptr )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RequestCreateRoom server GetserverInstance Failed" ) );
		return;
	}

	if ( !RoomName_TextBox )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RoomName_TextBox nullptr" ) );
		return;
	}

	if ( !RoomMax_TextBox )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RoomMax_TextBox nullptr" ) );
		return;
	}


	FString message = "O ";
	message += RoomMax_TextBox->GetText( ).ToString( );
	message += " ";
	message += RoomName_TextBox->GetText( ).ToString( );
	server->SendPacket( message );

	this->RemoveFromParent();
}
