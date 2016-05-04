//    This sample illustrates how to develop a simple TCP client application
//    that can send a simple "hello" message to a TCP server listening on port 5150.
//    This sample is implemented as a console-style application and simply prints
//    status messages a connection is made and when data is sent to the server.
//
#include "tcpClient.h"

SOCKET sClient;

void initSocket()
{
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() for sClient failed!\n");
		return;
	}
	return;
}

void connectToSever(SOCKADDR_IN* ServerAddr)
{
	printf("We are trying to connect to %s:%d...\n", inet_ntoa(ServerAddr->sin_addr), htons(ServerAddr->sin_port));
	if (connect(sClient, (SOCKADDR *)ServerAddr, sizeof(*ServerAddr)) == SOCKET_ERROR)
	{
		printf("connect failed with error %d\n", WSAGetLastError());
		closesocket(sClient);
		WSACleanup();
		return;
	}
	printf("Our connection succeeded.\n");
	return;
}

void sendToServer(const char* str)
{
	int Ret;
	printf("Server will now try to send a message to client.\n");
	if ((Ret = send(sClient, str, strlen(str) + 1, 0)) == SOCKET_ERROR)
	{
		printf("send failed with error %d\n", WSAGetLastError());
		closesocket(sClient);
		WSACleanup();
		return;
	}
	printf("Server successfully sent %d byte(s).\n", Ret);
	return;
}

void recvFromClient(SOCKET* s)
{
	int Ret;
	char DataBuffer[1024];
	printf("Server will now try to receive a message from client.\n");
	if ((Ret = recv(*s, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR)
	{
		printf("recv failed with error %d\n", WSAGetLastError());
		closesocket(*s);
		WSACleanup();
		return;
	}
	printf("Server successfully received %d byte(s): %s\n", Ret, DataBuffer);
	return;
}


void sendToClient(SOCKET* s, const char* str)
{
	int Ret;
	printf("Client will now try to send a message to server.\n");
	if ((Ret = send(*s, str, strlen(str) + 1, 0)) == SOCKET_ERROR)
	{
		printf("send failed with error %d\n", WSAGetLastError());
		closesocket(*s);
		WSACleanup();
		return;
	}
	printf("Client successfully sent %d byte(s).\n", Ret);
	return;
}

void recvFromServer()
{
	int Ret;
	char DataBuffer[1024];
	printf("Client will now try to receive a message from server.\n");
	if ((Ret = recv(sClient, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR)
	{
		printf("recv failed with error %d\n", WSAGetLastError());
		closesocket(sClient);
		WSACleanup();
		return;
	}
	printf("Client successfully received %d byte(s): %s\n", Ret, DataBuffer);
	return;
}