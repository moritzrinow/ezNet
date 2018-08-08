// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include <WinSock2.h>
#include "Common/Public/Defines.h"

#pragma comment(lib, "Ws2_32.lib")

EZNET_BEGIN

typedef SOCKET NativeSocket;
typedef sockaddr NativeSockAddr;
typedef sockaddr_in NativeSockAddrIn;

EZNET_END