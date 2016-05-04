#pragma once
#if !defined TCPCLIENT_H
#define TCPCLIETN_H
#include "stdafx.h"

void initSocket();
void sendToServer(SOCKADDR_IN* server, const char* str);
void recvFromClient(SOCKET* s, SOCKADDR_IN* client);
void sendToClient(SOCKET* s, SOCKADDR_IN* client, const char* str);
void recvFromServer(SOCKADDR_IN* server);

#endif