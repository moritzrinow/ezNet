// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")
#else // Unix
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#endif // _WIN32

#include "Common/Public/Defines.h"

EZNET_BEGIN

typedef SOCKET NativeSocket;
typedef sockaddr NativeSockAddr;
typedef sockaddr_in NativeSockAddrIn;

EZNET_END