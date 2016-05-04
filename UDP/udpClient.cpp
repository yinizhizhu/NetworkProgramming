//    This sample illustrates how to develop a simple TCP client application
//    that can send a simple "hello" message to a TCP server listening on port 5150.
//    This sample is implemented as a console-style application and simply prints
//    status messages a connection is made and when data is sent to the server.
//
#include "udpClient.h"

SOCKET SendClient;

void initSocket()
{
	SendClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SendClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() for sClient failed!\n");
		return;
	}
	return;
}

void sendToServer(SOCKADDR_IN* server, const char* str)
{
	int Ret;
	printf("Server will now try to send a message to client.\n");
	if ((Ret = sendto(SendClient, str, strlen(str) + 1, 0, (SOCKADDR *)server, sizeof(*server))) == SOCKET_ERROR)
	{
		printf("send failed with error %d\n", WSAGetLastError());
		closesocket(SendClient);
		WSACleanup();
		return;
	}
	printf("Server successfully sent %d byte(s).\n", Ret);
	return;
}

void recvFromClient(SOCKET* s, SOCKADDR_IN* client)
{
	int Ret;
	int len = sizeof(*client);
	char DataBuffer[1024];
	printf("Server will now try to receive a message from client.\n");
	if ((Ret = recvfrom(*s, DataBuffer, sizeof(DataBuffer), 0, (SOCKADDR *)client, &len)) == SOCKET_ERROR)
	{
		printf("recv failed with error %d\n", WSAGetLastError());
		closesocket(*s);
		WSACleanup();
		return;
	}
	printf("Server successfully received %d byte(s): %s\n", Ret, DataBuffer);
	return;
}


void sendToClient(SOCKET* s, SOCKADDR_IN* client, const char* str)
{
	int Ret;
	printf("Client will now try to send a message to server.\n");
	if ((Ret = sendto(*s, str, strlen(str) + 1, 0, (SOCKADDR *)client, sizeof(*client))) == SOCKET_ERROR)
	{
		printf("send failed with error %d\n", WSAGetLastError());
		closesocket(*s);
		WSACleanup();
		return;
	}
	printf("Client successfully sent %d byte(s).\n", Ret);
	return;
}

void recvFromServer(SOCKADDR_IN* server)
{
	int Ret;
	int len = sizeof(*server);
	char DataBuffer[1024];
	printf("Client will now try to receive a message from server.\n");
	if ((Ret = recvfrom(SendClient, DataBuffer, sizeof(DataBuffer), 0, (SOCKADDR *)server, &len)) == SOCKET_ERROR)
	{
		printf("recv failed with error %d\n", WSAGetLastError());
		closesocket(SendClient);
		WSACleanup();
		return;
	}
	printf("Client successfully received %d byte(s): %s\n", Ret, DataBuffer);
	return;
}