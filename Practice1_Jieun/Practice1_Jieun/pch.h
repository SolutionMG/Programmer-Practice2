

#ifndef PCH_H
#define PCH_H


///network
#include<WS2tcpip.h>
#include<MSWSock.h>
#pragma comment(lib,"WS2_32.lib")
#pragma comment(lib, "mswsock.lib")


///C++
#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>
#include<mutex>


///USER
#include "Define.h"


///OPERATION TYPE
enum class EOperationType : char
{
	RECV, SEND, ACCEPT, END
};


///EXTEND OVERLAPPED
struct WSAOVERLAPPED_EXTEND
{
	WSAOVERLAPPED	over;
	WSABUF			wsaBuffer;
	char			networkBuffer[InitailizeServer::MAX_BUFFERSIZE];
	EOperationType	opType;
	SOCKET			socket;
};
#endif //PCH_H
