// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "ISocket.h"

EZNET_BEGIN

class SocketFactory;

/*
* Simple factory for creating and destroying ISocket objects.
*/
class SocketFactory {

public:

  /*
  * Creates a blocking socket.
  */
  static ISocket* CreateSocket();

  /*
  * Creates a socket, which blocking mode depends on the input parameter.
  */
  static ISocket* CreateSocket(bool blocking);

  /*
  * Simply calls delete on the ISocket object.
  * Only call this on an ISocket object, that was created on the heap.
  */
  static void DestroySocket(ISocket* socket);
};

EZNET_END