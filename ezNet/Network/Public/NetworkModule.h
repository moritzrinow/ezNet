// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Common/Public/Assert.h"
#include "SocketFactory.h"

EZNET_BEGIN

namespace BNNetwork {

  /*
  * Initialize WinSock lib.
  * Returns false on error / breaks in debug mode.
  */
  inline bool InitWSA()
  {
    WSADATA data;
    int32 result = WSAStartup(MAKEWORD(2, 2), &data);

    if (result != NO_ERROR) {
      bn_debug_break();
      return false;
    }

    return true;
  }

  /*
  * Cleans up the WinSock lib.
  */
  inline void CleanupWSA()
  {
    WSACleanup();
  }

  /*
  * Gets the error code of the last WinSock error.
  */
  inline int32 GetLastWSAError()
  {
    return WSAGetLastError();
  }
}

EZNET_END