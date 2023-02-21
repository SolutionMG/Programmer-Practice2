 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ServerManager.generated.h"

#define SERVERIP "127.0.0.1"

 /**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UServerManager : public UGameInstance
{
	GENERATED_BODY()
private:
	FSocket* m_socket;
	FString m_name;
	FString m_encodingBuffer;
public:

	///ServerManager �ʱ�ȭ �Լ�
	virtual void Init( ) override;

	///ServerManager ���� �� Cleanup �Լ�
	virtual void Shutdown( ) override;

	UFUNCTION( BlueprintCallable, Category = "Server Communication" )
	bool ConnectToServer();

	///��Ŷ Ÿ�Կ� ���� ���� ��
	//UFUNCTION( BlueprintCallable, Category = "Server Communication" )
	//void SendPacket( int32 type, const FString& packet );

	///���� ���ڿ� ���� ���� ��
	UFUNCTION(BlueprintCallable, Category = "Server Communication")
	bool SendPacket(const FString& packet);

	UFUNCTION( BlueprintCallable, Category = "Server Communication" )
	bool ReceivePacket();

	bool ProcessPacket( const FString& packet );
};

