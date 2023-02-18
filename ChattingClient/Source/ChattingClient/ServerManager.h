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

#define SERVERPORT 9000
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
public:

	virtual void Init() override;

	UFUNCTION( BlueprintCallable, Category = "Server Communication" )
	bool ConnectToServer();

private:
	int CreateSocket();

};
