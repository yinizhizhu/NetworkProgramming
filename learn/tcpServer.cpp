//    This sample illustrates how to develop a simple TCP server application
//    that listens for a TCP connection on port 5150 and receives data. This 
//    sample is implemented as a console-style application and simply prints 
//    status messages when a connection is accepted and when data is received 
//    by the server.
//
#include "tcpServer.h"

void runServer()
{
	WSADATA              wsaData;
	SOCKET               ListeningSocket;
	SOCKET               NewConnection;
	SOCKADDR_IN          ServerAddr;
	SOCKADDR_IN          ClientAddr;
	int                  ClientAddrLen;
	int                  Port = 5150;
	int                  Ret;

	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}

	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = htons(Port);
	ClientAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ClientAddrLen = sizeof(ClientAddr);

	if (bind(ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return;
	}

	if (listen(ListeningSocket, 5) == SOCKET_ERROR)
	{
		printf("listen failed with error %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return;
	}

	printf("We are awaiting a connection on port %d.\n", Port);

	initSocket();//init sClient
	connectToSever(&ServerAddr);//connect to server

	if ((NewConnection = accept(ListeningSocket, (SOCKADDR *)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET)
	{
		printf("accept failed with error %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return;
	}

	printf("We successfully got a connection from %s:%d.\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

	closesocket(ListeningSocket);

	printf("We are waiting to receive data...\n");

	sendToServer("We are the champion");//client send to server
	recvFromClient(&NewConnection);//server recieve from client
	sendToClient(&NewConnection, "We keep on fighting till the end!");//server send to client
	recvFromServer();//client revieve from server

	printf("We are now going to close the client connection.\n");

	closesocket(NewConnection);

	WSACleanup();
}
