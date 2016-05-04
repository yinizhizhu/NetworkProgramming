#pragma once
#if !defined TCPCLIENT_H
#define TCPCLIETN_H
#include "stdafx.h"

void initSocket();
void connectToSever(SOCKADDR_IN* ServerAddr);
void sendToServer(const char* str);
void recvFromClient(SOCKET* s);
void sendToClient(SOCKET* s, const char* str);
void recvFromServer();

#endif