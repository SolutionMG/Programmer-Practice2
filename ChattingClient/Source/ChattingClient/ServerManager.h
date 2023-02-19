 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"
#include<WS2tcpip.h>
#include<MSWSock.h>
#pragma comment(lib,"WS2_32.lib")
#pragma comment(lib, "mswsock.lib")
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

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
	SOCKET m_socket;
	SOCKADDR_IN m_sockAddr;
	FString m_name;
public:

	///ServerManager 초기화 함수
	virtual void Init( ) override;

	///ServerManager 종료 전 Cleanup 함수
	virtual void Shutdown( ) override;

	UFUNCTION( BlueprintCallable, Category = "Server Communication" )
	bool ConnectToServer();

	UFUNCTION( BlueprintCallable, Category = "Server Communication" )
	void SendPacket( int32 type, const FString& packet );

	UFUNCTION( BlueprintCallable, Category = "Server Communication" )
	void ReceivePacket( );

private:
	int CreateSocket();

};
